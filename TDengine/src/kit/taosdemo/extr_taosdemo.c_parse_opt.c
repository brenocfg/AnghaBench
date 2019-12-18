#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
struct arguments {char* host; char* user; char* password; char* output_file; char* database; char** datatype; char* tb_prefix; int use_metric; int insert_only; int abort; void* len_of_binary; void* num_of_CPR; void* num_of_DPT; void* num_of_tables; void* num_of_RPR; void* num_of_connections; void* mode; void* port; } ;
struct argp_state {struct arguments* input; } ;
typedef  int error_t ;

/* Variables and functions */
 int ARGP_ERR_UNKNOWN ; 
#define  ARGP_KEY_ARG 129 
#define  OPT_ABORT 128 
 int /*<<< orphan*/  TSDB_OPTION_CONFIGDIR ; 
 int /*<<< orphan*/  argp_error (struct argp_state*,char*) ; 
 int /*<<< orphan*/  argp_usage (struct argp_state*) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  taos_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

__attribute__((used)) static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  wordexp_t full_path;
  char **sptr;
  switch (key) {
    case 'h':
      arguments->host = arg;
      break;
    case 'p':
      arguments->port = atoi(arg);
      break;
    case 'u':
      arguments->user = arg;
      break;
    case 'a':
      arguments->password = arg;
      break;
    case 'o':
      arguments->output_file = arg;
      break;
    case 'q':
      arguments->mode = atoi(arg);
      break;
    case 'c':
      arguments->num_of_connections = atoi(arg);
      break;
    case 'r':
      arguments->num_of_RPR = atoi(arg);
      break;
    case 't':
      arguments->num_of_tables = atoi(arg);
      break;
    case 'n':
      arguments->num_of_DPT = atoi(arg);
      break;
    case 'd':
      arguments->database = arg;
      break;
    case 'l':
      arguments->num_of_CPR = atoi(arg);
      break;
    case 'b':
      sptr = arguments->datatype;
      if (strstr(arg, ",") == NULL) {
        if (strcasecmp(arg, "INT") != 0 && strcasecmp(arg, "FLOAT") != 0 &&
            strcasecmp(arg, "TINYINT") != 0 && strcasecmp(arg, "BOOL") != 0 &&
            strcasecmp(arg, "SMALLINT") != 0 &&
            strcasecmp(arg, "BIGINT") != 0 && strcasecmp(arg, "DOUBLE") != 0 &&
            strcasecmp(arg, "BINARY")) {
          argp_error(state, "Invalid data_type!");
        }
        sptr[0] = arg;
      } else {
        int index = 0;
        char *dupstr = strdup(arg);
        char *running = dupstr;
        char *token = strsep(&running, ",");
        while (token != NULL) {
          if (strcasecmp(token, "INT") != 0 &&
              strcasecmp(token, "FLOAT") != 0 &&
              strcasecmp(token, "TINYINT") != 0 &&
              strcasecmp(token, "BOOL") != 0 &&
              strcasecmp(token, "SMALLINT") != 0 &&
              strcasecmp(token, "BIGINT") != 0 &&
              strcasecmp(token, "DOUBLE") != 0 && strcasecmp(token, "BINARY")) {
            argp_error(state, "Invalid data_type!");
          }
          sptr[index++] = token;
          token = strsep(&running, ", ");
        }
      }
      break;
    case 'w':
      arguments->len_of_binary = atoi(arg);
      break;
    case 'm':
      arguments->tb_prefix = arg;
      break;
    case 'M':
      arguments->use_metric = true;
      break;
    case 'x':
      arguments->insert_only = true;
      break;
    case 'f':
      if (wordexp(arg, &full_path, 0) != 0) {
        fprintf(stderr, "Invalid path %s\n", arg);
        return -1;
      }
      taos_options(TSDB_OPTION_CONFIGDIR, full_path.we_wordv[0]);
      wordfree(&full_path);
      break;
    case OPT_ABORT:
      arguments->abort = 1;
      break;
    case ARGP_KEY_ARG:
      /*arguments->arg_list = &state->argv[state->next-1];
      state->next = state->argc;*/
      argp_usage(state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}