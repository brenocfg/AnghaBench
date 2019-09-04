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
struct OperationConfig {struct OperationConfig* next; struct OperationConfig* prev; struct GlobalConfig* global; int /*<<< orphan*/  easy; TYPE_1__* url_list; } ;
struct GlobalConfig {int /*<<< orphan*/  errors; struct OperationConfig* last; int /*<<< orphan*/  easy; struct OperationConfig* first; } ;
typedef  char* argv_item_t ;
struct TYPE_2__ {scalar_t__ url; } ;
typedef  scalar_t__ ParameterError ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ PARAM_ENGINES_REQUESTED ; 
 scalar_t__ PARAM_HELP_REQUESTED ; 
 scalar_t__ PARAM_MANUAL_REQUESTED ; 
 scalar_t__ PARAM_NEXT_OPERATION ; 
 scalar_t__ PARAM_NO_MEM ; 
 scalar_t__ PARAM_OK ; 
 scalar_t__ PARAM_VERSION_INFO_REQUESTED ; 
 int TRUE ; 
 int /*<<< orphan*/  config_init (struct OperationConfig*) ; 
 scalar_t__ getparameter (char*,char*,int*,struct GlobalConfig*,struct OperationConfig*) ; 
 int /*<<< orphan*/  helpf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 struct OperationConfig* malloc (int) ; 
 char* param2text (scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 

ParameterError parse_args(struct GlobalConfig *config, int argc,
                          argv_item_t argv[])
{
  int i;
  bool stillflags;
  char *orig_opt = NULL;
  ParameterError result = PARAM_OK;
  struct OperationConfig *operation = config->first;

  for(i = 1, stillflags = TRUE; i < argc && !result; i++) {
    orig_opt = argv[i];

    if(stillflags && ('-' == argv[i][0])) {
      bool passarg;
      char *flag = argv[i];

      if(!strcmp("--", argv[i]))
        /* This indicates the end of the flags and thus enables the
           following (URL) argument to start with -. */
        stillflags = FALSE;
      else {
        char *nextarg = (i < (argc - 1)) ? argv[i + 1] : NULL;

        result = getparameter(flag, nextarg, &passarg, config, operation);
        if(result == PARAM_NEXT_OPERATION) {
          /* Reset result as PARAM_NEXT_OPERATION is only used here and not
             returned from this function */
          result = PARAM_OK;

          if(operation->url_list && operation->url_list->url) {
            /* Allocate the next config */
            operation->next = malloc(sizeof(struct OperationConfig));
            if(operation->next) {
              /* Initialise the newly created config */
              config_init(operation->next);

              /* Copy the easy handle */
              operation->next->easy = config->easy;

              /* Set the global config pointer */
              operation->next->global = config;

              /* Update the last operation pointer */
              config->last = operation->next;

              /* Move onto the new config */
              operation->next->prev = operation;
              operation = operation->next;
            }
            else
              result = PARAM_NO_MEM;
          }
        }
        else if(!result && passarg)
          i++; /* we're supposed to skip this */
      }
    }
    else {
      bool used;

      /* Just add the URL please */
      result = getparameter((char *)"--url", argv[i], &used, config,
                            operation);
    }
  }

  if(result && result != PARAM_HELP_REQUESTED &&
     result != PARAM_MANUAL_REQUESTED &&
     result != PARAM_VERSION_INFO_REQUESTED &&
     result != PARAM_ENGINES_REQUESTED) {
    const char *reason = param2text(result);

    if(orig_opt && strcmp(":", orig_opt))
      helpf(config->errors, "option %s: %s\n", orig_opt, reason);
    else
      helpf(config->errors, "%s\n", reason);
  }

  return result;
}