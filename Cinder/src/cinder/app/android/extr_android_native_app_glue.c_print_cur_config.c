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
struct android_app {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  AConfiguration_getCountry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AConfiguration_getDensity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getKeyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getKeysHidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getLanguage (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AConfiguration_getMcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getMnc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getNavHidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getNavigation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getOrientation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getScreenLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getScreenSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getSdkVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getTouchscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getUiModeNight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_getUiModeType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGV (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_cur_config(struct android_app* android_app) {
    char lang[2], country[2];
    AConfiguration_getLanguage(android_app->config, lang);
    AConfiguration_getCountry(android_app->config, country);

    LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
            "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
            "modetype=%d modenight=%d",
            AConfiguration_getMcc(android_app->config),
            AConfiguration_getMnc(android_app->config),
            lang[0], lang[1], country[0], country[1],
            AConfiguration_getOrientation(android_app->config),
            AConfiguration_getTouchscreen(android_app->config),
            AConfiguration_getDensity(android_app->config),
            AConfiguration_getKeyboard(android_app->config),
            AConfiguration_getNavigation(android_app->config),
            AConfiguration_getKeysHidden(android_app->config),
            AConfiguration_getNavHidden(android_app->config),
            AConfiguration_getSdkVersion(android_app->config),
            AConfiguration_getScreenSize(android_app->config),
            AConfiguration_getScreenLong(android_app->config),
            AConfiguration_getUiModeType(android_app->config),
            AConfiguration_getUiModeNight(android_app->config));
}