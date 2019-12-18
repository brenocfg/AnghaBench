#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* post_test ) (void*) ;int /*<<< orphan*/  (* loop ) (void*,void*) ;int /*<<< orphan*/  (* def_param ) (void*) ;int /*<<< orphan*/  (* pre_test ) (void**) ;} ;
typedef  TYPE_1__ ptest_func_t ;
struct TYPE_6__ {int pset_num; int /*<<< orphan*/  pset_size; void* param_group; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ param_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stub1 (void**) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*,void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 

void test_serializer(const param_group_t *param_group, const ptest_func_t* test_func)
{
    ESP_LOGI("test", "run test: %s", param_group->name);
    //in this test case, we want to make two devices as similar as possible, so use the same context
    void *context = NULL;
    test_func->pre_test(&context);

    void *pset = param_group->param_group;
    for (int i = param_group->pset_num; i >0; i--) {
        if (test_func->def_param) test_func->def_param(pset);
        test_func->loop(pset, context);
        pset+=param_group->pset_size;
    }

    test_func->post_test(context);
    free(context);
    context = NULL;
}