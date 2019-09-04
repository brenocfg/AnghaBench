#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct OperationConfig {struct GlobalConfig* global; struct OperationConfig* next; struct OperationConfig* prev; int /*<<< orphan*/  easy; TYPE_1__* url_list; } ;
struct GlobalConfig {struct OperationConfig* last; int /*<<< orphan*/  easy; struct OperationConfig* first; } ;
typedef  int /*<<< orphan*/  filebuffer ;
struct TYPE_2__ {scalar_t__ url; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CURLRC ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  DIR_CHAR ; 
 int FALSE ; 
 int /*<<< orphan*/  FOPEN_READTEXT ; 
 scalar_t__ ISSEP (char,int) ; 
 scalar_t__ ISSPACE (char) ; 
 int PARAM_ENGINES_REQUESTED ; 
 int PARAM_GOT_EXTRA_PARAMETER ; 
 int PARAM_HELP_REQUESTED ; 
 int PARAM_MANUAL_REQUESTED ; 
 int PARAM_NEXT_OPERATION ; 
 int PARAM_NO_MEM ; 
 int PARAM_OK ; 
 int PARAM_VERSION_INFO_REQUESTED ; 
 int TRUE ; 
 int /*<<< orphan*/  config_init (struct OperationConfig*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,int /*<<< orphan*/ ) ; 
 int getparameter (char*,char*,int*,struct GlobalConfig*,struct OperationConfig*) ; 
 char* homedir () ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char*,int /*<<< orphan*/ ,char*) ; 
 char* my_get_line (int /*<<< orphan*/ *) ; 
 char* param2text (int) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unslashquote (char*,char*) ; 
 int /*<<< orphan*/  warnf (struct GlobalConfig*,char*,char const*,int,char*,...) ; 

int parseconfig(const char *filename, struct GlobalConfig *global)
{
  FILE *file;
  char filebuffer[512];
  bool usedarg = FALSE;
  int rc = 0;
  struct OperationConfig *operation = global->first;

  if(!filename || !*filename) {
    /* NULL or no file name attempts to load .curlrc from the homedir! */

#ifndef __AMIGA__
    char *home = homedir();    /* portable homedir finder */
    filename = CURLRC;   /* sensible default */
    if(home) {
      if(strlen(home) < (sizeof(filebuffer) - strlen(CURLRC))) {
        msnprintf(filebuffer, sizeof(filebuffer),
                  "%s%s%s", home, DIR_CHAR, CURLRC);

#ifdef WIN32
        /* Check if the file exists - if not, try CURLRC in the same
         * directory as our executable
         */
        file = fopen(filebuffer, FOPEN_READTEXT);
        if(file != NULL) {
          fclose(file);
          filename = filebuffer;
        }
        else {
          /* Get the filename of our executable. GetModuleFileName is
           * already declared via inclusions done in setup header file.
           * We assume that we are using the ASCII version here.
           */
          int n = GetModuleFileNameA(0, filebuffer, sizeof(filebuffer));
          if(n > 0 && n < (int)sizeof(filebuffer)) {
            /* We got a valid filename - get the directory part */
            char *lastdirchar = strrchr(filebuffer, '\\');
            if(lastdirchar) {
              size_t remaining;
              *lastdirchar = 0;
              /* If we have enough space, build the RC filename */
              remaining = sizeof(filebuffer) - strlen(filebuffer);
              if(strlen(CURLRC) < remaining - 1) {
                msnprintf(lastdirchar, remaining,
                          "%s%s", DIR_CHAR, CURLRC);
                /* Don't bother checking if it exists - we do that later */
                filename = filebuffer;
              }
            }
          }
        }
#else /* WIN32 */
        filename = filebuffer;
#endif /* WIN32 */
      }
      Curl_safefree(home); /* we've used it, now free it */
    }

# else /* __AMIGA__ */
    /* On AmigaOS all the config files are into env:
     */
    filename = "ENV:" CURLRC;

#endif
  }

  if(strcmp(filename, "-"))
    file = fopen(filename, FOPEN_READTEXT);
  else
    file = stdin;

  if(file) {
    char *line;
    char *aline;
    char *option;
    char *param;
    int lineno = 0;
    bool dashed_option;

    while(NULL != (aline = my_get_line(file))) {
      int res;
      bool alloced_param = FALSE;
      lineno++;
      line = aline;

      /* line with # in the first non-blank column is a comment! */
      while(*line && ISSPACE(*line))
        line++;

      switch(*line) {
      case '#':
      case '/':
      case '\r':
      case '\n':
      case '*':
      case '\0':
        Curl_safefree(aline);
        continue;
      }

      /* the option keywords starts here */
      option = line;

      /* the option starts with a dash? */
      dashed_option = option[0]=='-'?TRUE:FALSE;

      while(*line && !ISSPACE(*line) && !ISSEP(*line, dashed_option))
        line++;
      /* ... and has ended here */

      if(*line)
        *line++ = '\0'; /* zero terminate, we have a local copy of the data */

#ifdef DEBUG_CONFIG
      fprintf(stderr, "GOT: %s\n", option);
#endif

      /* pass spaces and separator(s) */
      while(*line && (ISSPACE(*line) || ISSEP(*line, dashed_option)))
        line++;

      /* the parameter starts here (unless quoted) */
      if(*line == '\"') {
        /* quoted parameter, do the quote dance */
        line++;
        param = malloc(strlen(line) + 1); /* parameter */
        if(!param) {
          /* out of memory */
          Curl_safefree(aline);
          rc = 1;
          break;
        }
        alloced_param = TRUE;
        (void)unslashquote(line, param);
      }
      else {
        param = line; /* parameter starts here */
        while(*line && !ISSPACE(*line))
          line++;

        if(*line) {
          *line = '\0'; /* zero terminate */

          /* to detect mistakes better, see if there's data following */
          line++;
          /* pass all spaces */
          while(*line && ISSPACE(*line))
            line++;

          switch(*line) {
          case '\0':
          case '\r':
          case '\n':
          case '#': /* comment */
            break;
          default:
            warnf(operation->global, "%s:%d: warning: '%s' uses unquoted "
                  "white space in the line that may cause side-effects!\n",
                  filename, lineno, option);
          }
        }
        if(!*param)
          /* do this so getparameter can check for required parameters.
             Otherwise it always thinks there's a parameter. */
          param = NULL;
      }

#ifdef DEBUG_CONFIG
      fprintf(stderr, "PARAM: \"%s\"\n",(param ? param : "(null)"));
#endif
      res = getparameter(option, param, &usedarg, global, operation);

      if(!res && param && *param && !usedarg)
        /* we passed in a parameter that wasn't used! */
        res = PARAM_GOT_EXTRA_PARAMETER;

      if(res == PARAM_NEXT_OPERATION) {
        if(operation->url_list && operation->url_list->url) {
          /* Allocate the next config */
          operation->next = malloc(sizeof(struct OperationConfig));
          if(operation->next) {
            /* Initialise the newly created config */
            config_init(operation->next);

            /* Copy the easy handle */
            operation->next->easy = global->easy;

            /* Set the global config pointer */
            operation->next->global = global;

            /* Update the last operation pointer */
            global->last = operation->next;

            /* Move onto the new config */
            operation->next->prev = operation;
            operation = operation->next;
          }
          else
            res = PARAM_NO_MEM;
        }
      }

      if(res != PARAM_OK && res != PARAM_NEXT_OPERATION) {
        /* the help request isn't really an error */
        if(!strcmp(filename, "-")) {
          filename = "<stdin>";
        }
        if(res != PARAM_HELP_REQUESTED &&
           res != PARAM_MANUAL_REQUESTED &&
           res != PARAM_VERSION_INFO_REQUESTED &&
           res != PARAM_ENGINES_REQUESTED) {
          const char *reason = param2text(res);
          warnf(operation->global, "%s:%d: warning: '%s' %s\n",
                filename, lineno, option, reason);
        }
      }

      if(alloced_param)
        Curl_safefree(param);

      Curl_safefree(aline);
    }
    if(file != stdin)
      fclose(file);
  }
  else
    rc = 1; /* couldn't open the file */

  return rc;
}