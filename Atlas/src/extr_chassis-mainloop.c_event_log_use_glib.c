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
typedef  int /*<<< orphan*/  GLogLevelFlags ;

/* Variables and functions */
 int /*<<< orphan*/  G_LOG_DOMAIN ; 
 int /*<<< orphan*/  G_LOG_LEVEL_CRITICAL ; 
 int /*<<< orphan*/  G_LOG_LEVEL_DEBUG ; 
 int /*<<< orphan*/  G_LOG_LEVEL_MESSAGE ; 
 int /*<<< orphan*/  G_LOG_LEVEL_WARNING ; 
 int _EVENT_LOG_DEBUG ; 
 int _EVENT_LOG_ERR ; 
 int _EVENT_LOG_MSG ; 
 int _EVENT_LOG_WARN ; 
 int /*<<< orphan*/  g_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void event_log_use_glib(int libevent_log_level, const char *msg) {
	/* map libevent to glib log-levels */

	GLogLevelFlags glib_log_level = G_LOG_LEVEL_DEBUG;

	if (libevent_log_level == _EVENT_LOG_DEBUG) glib_log_level = G_LOG_LEVEL_DEBUG;
	else if (libevent_log_level == _EVENT_LOG_MSG) glib_log_level = G_LOG_LEVEL_MESSAGE;
	else if (libevent_log_level == _EVENT_LOG_WARN) glib_log_level = G_LOG_LEVEL_WARNING;
	else if (libevent_log_level == _EVENT_LOG_ERR) glib_log_level = G_LOG_LEVEL_CRITICAL;
    
    /*only error to be logged*/
    if (libevent_log_level == _EVENT_LOG_ERR) {
        g_log(G_LOG_DOMAIN, glib_log_level, "(libevent) %s", msg);
    }
}