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
struct OperationConfig {int dummy; } ;
struct GlobalConfig {int showerror; TYPE_1__* first; TYPE_1__* last; int /*<<< orphan*/  parallel_max; int /*<<< orphan*/  styled_output; int /*<<< orphan*/  errors; } ;
struct TYPE_4__ {struct GlobalConfig* global; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_FAILED_INIT ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 int /*<<< orphan*/  PARALLEL_DEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 int _STAT_DIRSIZE ; 
 int _STAT_EXEC_MAGIC ; 
 int _STAT_INODE ; 
 int _djstat_flags ; 
 int /*<<< orphan*/  config_init (TYPE_1__*) ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ get_libcurl_info () ; 
 int /*<<< orphan*/  helpf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static CURLcode main_init(struct GlobalConfig *config)
{
  CURLcode result = CURLE_OK;

#if defined(__DJGPP__) || defined(__GO32__)
  /* stop stat() wasting time */
  _djstat_flags |= _STAT_INODE | _STAT_EXEC_MAGIC | _STAT_DIRSIZE;
#endif

  /* Initialise the global config */
  config->showerror = -1;             /* Will show errors */
  config->errors = stderr;            /* Default errors to stderr */
  config->styled_output = TRUE;       /* enable detection */
  config->parallel_max = PARALLEL_DEFAULT;

  /* Allocate the initial operate config */
  config->first = config->last = malloc(sizeof(struct OperationConfig));
  if(config->first) {
    /* Perform the libcurl initialization */
    result = curl_global_init(CURL_GLOBAL_DEFAULT);
    if(!result) {
      /* Get information about libcurl */
      result = get_libcurl_info();

      if(!result) {
        /* Initialise the config */
        config_init(config->first);
        config->first->global = config;
      }
      else {
        helpf(stderr, "error retrieving curl library information\n");
        free(config->first);
      }
    }
    else {
      helpf(stderr, "error initializing curl library\n");
      free(config->first);
    }
  }
  else {
    helpf(stderr, "error initializing curl\n");
    result = CURLE_FAILED_INIT;
  }

  return result;
}