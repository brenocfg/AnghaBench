#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct OperationConfig {struct OperationConfig* next; int /*<<< orphan*/  url_list; } ;
struct GlobalConfig {int /*<<< orphan*/  errors; scalar_t__ libcurl; struct OperationConfig* first; struct OperationConfig* current; } ;
typedef  int /*<<< orphan*/  argv_item_t ;
typedef  scalar_t__ ParameterError ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURLSH ;

/* Variables and functions */
 scalar_t__ CURLE_FAILED_INIT ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_UNSUPPORTED_PROTOCOL ; 
 int /*<<< orphan*/  CURLSHOPT_SHARE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_CONNECT ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_COOKIE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_DNS ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_PSL ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_SSL_SESSION ; 
 int /*<<< orphan*/  LC_ALL ; 
 scalar_t__ PARAM_ENGINES_REQUESTED ; 
 scalar_t__ PARAM_HELP_REQUESTED ; 
 scalar_t__ PARAM_LIBCURL_UNSUPPORTED_PROTOCOL ; 
 scalar_t__ PARAM_MANUAL_REQUESTED ; 
 scalar_t__ PARAM_VERSION_INFO_REQUESTED ; 
 int /*<<< orphan*/  curl_share_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_share_init () ; 
 int /*<<< orphan*/  curl_share_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_strequal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dumpeasysrc (struct GlobalConfig*) ; 
 int /*<<< orphan*/  easysrc_cleanup () ; 
 scalar_t__ easysrc_init () ; 
 scalar_t__ get_args (struct OperationConfig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helpf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hugehelp () ; 
 scalar_t__ parse_args (struct GlobalConfig*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parseconfig (int /*<<< orphan*/ *,struct GlobalConfig*) ; 
 scalar_t__ run_all_transfers (struct GlobalConfig*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tool_help () ; 
 int /*<<< orphan*/  tool_list_engines () ; 
 int /*<<< orphan*/  tool_version_info () ; 

CURLcode operate(struct GlobalConfig *global, int argc, argv_item_t argv[])
{
  CURLcode result = CURLE_OK;

  /* Setup proper locale from environment */
#ifdef HAVE_SETLOCALE
  setlocale(LC_ALL, "");
#endif

  /* Parse .curlrc if necessary */
  if((argc == 1) ||
     (!curl_strequal(argv[1], "-q") &&
      !curl_strequal(argv[1], "--disable"))) {
    parseconfig(NULL, global); /* ignore possible failure */

    /* If we had no arguments then make sure a url was specified in .curlrc */
    if((argc < 2) && (!global->first->url_list)) {
      helpf(global->errors, NULL);
      result = CURLE_FAILED_INIT;
    }
  }

  if(!result) {
    /* Parse the command line arguments */
    ParameterError res = parse_args(global, argc, argv);
    if(res) {
      result = CURLE_OK;

      /* Check if we were asked for the help */
      if(res == PARAM_HELP_REQUESTED)
        tool_help();
      /* Check if we were asked for the manual */
      else if(res == PARAM_MANUAL_REQUESTED)
        hugehelp();
      /* Check if we were asked for the version information */
      else if(res == PARAM_VERSION_INFO_REQUESTED)
        tool_version_info();
      /* Check if we were asked to list the SSL engines */
      else if(res == PARAM_ENGINES_REQUESTED)
        tool_list_engines();
      else if(res == PARAM_LIBCURL_UNSUPPORTED_PROTOCOL)
        result = CURLE_UNSUPPORTED_PROTOCOL;
      else
        result = CURLE_FAILED_INIT;
    }
    else {
#ifndef CURL_DISABLE_LIBCURL_OPTION
      if(global->libcurl) {
        /* Initialise the libcurl source output */
        result = easysrc_init();
      }
#endif

      /* Perform the main operations */
      if(!result) {
        size_t count = 0;
        struct OperationConfig *operation = global->first;
        CURLSH *share = curl_share_init();
        if(!share) {
#ifndef CURL_DISABLE_LIBCURL_OPTION
          if(global->libcurl) {
            /* Cleanup the libcurl source output */
            easysrc_cleanup();
          }
#endif
          return CURLE_OUT_OF_MEMORY;
        }

        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_CONNECT);
        curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_PSL);

        /* Get the required arguments for each operation */
        do {
          result = get_args(operation, count++);

          operation = operation->next;
        } while(!result && operation);

        /* Set the current operation pointer */
        global->current = global->first;

        /* now run! */
        result = run_all_transfers(global, share, result);

        curl_share_cleanup(share);
#ifndef CURL_DISABLE_LIBCURL_OPTION
        if(global->libcurl) {
          /* Cleanup the libcurl source output */
          easysrc_cleanup();

          /* Dump the libcurl code if previously enabled */
          dumpeasysrc(global);
        }
#endif
      }
      else
        helpf(global->errors, "out of memory\n");
    }
  }

  return result;
}