#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/  jmethodID ;
typedef  int /*<<< orphan*/  jclass ;
typedef  int /*<<< orphan*/  jboolean ;
struct TYPE_19__ {int /*<<< orphan*/  gamename; int /*<<< orphan*/  peripheral; int /*<<< orphan*/  region; int /*<<< orphan*/  cdinfo; int /*<<< orphan*/  date; int /*<<< orphan*/  version; int /*<<< orphan*/  itemnum; int /*<<< orphan*/  company; int /*<<< orphan*/  system; } ;
struct TYPE_18__ {char* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewObject ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* NewStringUTF ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* FindClass ) (TYPE_1__**,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  TYPE_2__ GameInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GameInfoFromPath (char const*,TYPE_2__*) ; 
 char* stub1 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub13 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__**,int /*<<< orphan*/ ) ; 

jobject Java_org_yabause_android_YabauseRunnable_gameInfo( JNIEnv* env, jobject obj, jobject path )
{
    jmethodID cons;
    jboolean dummy;
    jclass c;
    jstring system, company, itemnum, version, date, cdinfo, region, peripheral, gamename;
    GameInfo info;
    const char * filename = (*env)->GetStringUTFChars(env, path, &dummy);

    if (! GameInfoFromPath(filename, &info))
    {
       return NULL;
    }

    c = (*env)->FindClass(env, "org/yabause/android/GameInfo");
    cons = (*env)->GetMethodID(env, c, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    system = (*env)->NewStringUTF(env, info.system);
    company = (*env)->NewStringUTF(env, info.company);
    itemnum = (*env)->NewStringUTF(env, info.itemnum);
    version = (*env)->NewStringUTF(env, info.version);
    date = (*env)->NewStringUTF(env, info.date);
    cdinfo = (*env)->NewStringUTF(env, info.cdinfo);
    region = (*env)->NewStringUTF(env, info.region);
    peripheral = (*env)->NewStringUTF(env, info.peripheral);
    gamename = (*env)->NewStringUTF(env, info.gamename);

    return (*env)->NewObject(env, c, cons, system, company, itemnum, version, date, cdinfo, region, peripheral, gamename);
}