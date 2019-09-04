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
struct GlobalConfig {int dummy; } ;
typedef  int /*<<< orphan*/  global ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  configure_terminal () ; 
 int /*<<< orphan*/  main_checkfds () ; 
 int /*<<< orphan*/  main_free (struct GlobalConfig*) ; 
 scalar_t__ main_init (struct GlobalConfig*) ; 
 int /*<<< orphan*/  memory_tracking_init () ; 
 int /*<<< orphan*/  memset (struct GlobalConfig*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ operate (struct GlobalConfig*,int,char**) ; 
 int /*<<< orphan*/  restore_terminal () ; 

int main(int argc, char *argv[])
{
  CURLcode result = CURLE_OK;
  struct GlobalConfig global;
  memset(&global, 0, sizeof(global));

  /* Perform any platform-specific terminal configuration */
  configure_terminal();

  main_checkfds();

#if defined(HAVE_SIGNAL) && defined(SIGPIPE)
  (void)signal(SIGPIPE, SIG_IGN);
#endif

  /* Initialize memory tracking */
  memory_tracking_init();

  /* Initialize the curl library - do not call any libcurl functions before
     this point */
  result = main_init(&global);

#ifdef WIN32
  /* Undocumented diagnostic option to list the full paths of all loaded
     modules, regardless of whether or not initialization succeeded. */
  if(argc == 2 && !strcmp(argv[1], "--dump-module-paths")) {
    struct curl_slist *item, *head = GetLoadedModulePaths();
    for(item = head; item; item = item->next) {
      printf("%s\n", item->data);
    }
    curl_slist_free_all(head);
    if(!result)
      main_free(&global);
  }
  else
#endif /* WIN32 */
  if(!result) {
    /* Start our curl operation */
    result = operate(&global, argc, argv);

#ifdef __SYMBIAN32__
    if(global.showerror)
      tool_pressanykey();
#endif

    /* Perform the main cleanup */
    main_free(&global);
  }

  /* Return the terminal to its original state */
  restore_terminal();

#ifdef __NOVELL_LIBC__
  if(getenv("_IN_NETWARE_BASH_") == NULL)
    tool_pressanykey();
#endif

#ifdef __VMS
  vms_special_exit(result, vms_show);
#else
  return (int)result;
#endif
}