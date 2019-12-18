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
typedef  void (* notify_notification_show_t ) (void*,char*) ;
typedef  void (* notify_notification_set_timeout_t ) (void*,int) ;
typedef  void* (* notify_notification_new_t ) (char*,char*,char*,char*) ;
typedef  void (* notify_init_t ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 

int notify(char *title, char *body, int timeout)
{
    /* http://stackoverflow.com/questions/13204177/how-to-find-out-if-running-from-terminal-or-gui */
    if (isatty(fileno(stdin))){
        /* We were launched from the command line. */
        printf("\n%s\n", title);
        printf("%s\n", body);
    }
    else
    {
        /* We were launched from inside the desktop */
        printf("\n%s\n", title);
        printf("%s\n", body);
        /* https://debian-administration.org/article/407/Creating_desktop_notifications */
        void *handle, *n;
        typedef void  (*notify_init_t)(char *);
        typedef void *(*notify_notification_new_t)( char *, char *, char *, char *);
        typedef void  (*notify_notification_set_timeout_t)( void *, int );
        typedef void (*notify_notification_show_t)(void *, char *);
        handle = NULL;
        if(handle == NULL)
            handle= dlopen("libnotify.so.3", RTLD_LAZY);
        if(handle == NULL)
            handle= dlopen("libnotify.so.4", RTLD_LAZY);
        if(handle == NULL)
            handle= dlopen("libnotify.so.5", RTLD_LAZY);
        if(handle == NULL)
            handle= dlopen("libnotify.so.6", RTLD_LAZY);
        if(handle == NULL)
            handle= dlopen("libnotify.so.7", RTLD_LAZY);
        if(handle == NULL)
            handle= dlopen("libnotify.so.8", RTLD_LAZY);
        
        if(handle == NULL)
        {
            printf("Failed to open libnotify.\n\n" );
        }
        notify_init_t init = (notify_init_t)dlsym(handle, "notify_init");
        if ( init == NULL  )
        {
            dlclose( handle );
            return 1;
        }
        init("AppImage");
        
        notify_notification_new_t nnn = (notify_notification_new_t)dlsym(handle, "notify_notification_new");
        if ( nnn == NULL  )
        {
            dlclose( handle );
            return 1;
        }
        n = nnn(title, body, NULL, NULL);
        notify_notification_set_timeout_t nnst = (notify_notification_set_timeout_t)dlsym(handle, "notify_notification_set_timeout");
        if ( nnst == NULL  )
        {
            dlclose( handle );
            return 1;
        }
        nnst(n, timeout); 
        notify_notification_show_t show = (notify_notification_show_t)dlsym(handle, "notify_notification_show");
        if ( init == NULL  )
        {
            dlclose( handle );
            return 1;
        }
        show(n, NULL );
        dlclose(handle );
    }
    return 0;
}