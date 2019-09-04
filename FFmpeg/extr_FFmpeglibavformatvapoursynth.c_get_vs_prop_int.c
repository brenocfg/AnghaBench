#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VSMap ;
struct TYPE_6__ {TYPE_1__* vsapi; } ;
typedef  TYPE_2__ VSContext ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {int (* propGetInt ) (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int stub1 (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int get_vs_prop_int(AVFormatContext *s, const VSMap *map, const char *name, int def)
{
    VSContext *vs = s->priv_data;
    int64_t res;
    int err = 1;

    res = vs->vsapi->propGetInt(map, name, 0, &err);
    return err || res < INT_MIN || res > INT_MAX ? def : res;
}