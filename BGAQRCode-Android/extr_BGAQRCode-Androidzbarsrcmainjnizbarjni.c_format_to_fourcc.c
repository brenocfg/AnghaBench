#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  jstring ;
struct TYPE_6__ {int (* GetStringLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetStringUTFRegion ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  throw_exc (TYPE_1__**,char*,char*) ; 

__attribute__((used)) static inline uint32_t
format_to_fourcc(JNIEnv *env,
                 jstring format)
{
    if(!format)
        goto invalid;

    int n = (*env)->GetStringLength(env, format);
    if(0 >= n || n > 4)
        goto invalid;

    char fmtstr[8];
    (*env)->GetStringUTFRegion(env, format, 0, n, fmtstr);

    uint32_t fourcc = 0;
    int i;
    for(i = 0; i < n; i++) {
        if(fmtstr[i] < ' ' || 'Z' < fmtstr[i] ||
           ('9' < fmtstr[i] && fmtstr[i] < 'A') ||
           (' ' < fmtstr[i] && fmtstr[i] < '0'))
            goto invalid;
        fourcc |= ((uint32_t)fmtstr[i]) << (8 * i);
    }
    return(fourcc);

invalid:
    throw_exc(env, "java/lang/IllegalArgumentException",
              "invalid format fourcc");
    return(0);
}