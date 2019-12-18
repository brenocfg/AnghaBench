#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * free_model; int /*<<< orphan*/ * execute_model; int /*<<< orphan*/ * load_model; } ;
typedef  TYPE_1__ DNNModule ;
typedef  int DNNBackendType ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  DNN_NATIVE 129 
#define  DNN_TF 128 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_malloc (int) ; 
 int /*<<< orphan*/  ff_dnn_execute_model_native ; 
 int /*<<< orphan*/  ff_dnn_execute_model_tf ; 
 int /*<<< orphan*/  ff_dnn_free_model_native ; 
 int /*<<< orphan*/  ff_dnn_free_model_tf ; 
 int /*<<< orphan*/  ff_dnn_load_model_native ; 
 int /*<<< orphan*/  ff_dnn_load_model_tf ; 

DNNModule *ff_get_dnn_module(DNNBackendType backend_type)
{
    DNNModule *dnn_module;

    dnn_module = av_malloc(sizeof(DNNModule));
    if(!dnn_module){
        return NULL;
    }

    switch(backend_type){
    case DNN_NATIVE:
        dnn_module->load_model = &ff_dnn_load_model_native;
        dnn_module->execute_model = &ff_dnn_execute_model_native;
        dnn_module->free_model = &ff_dnn_free_model_native;
        break;
    case DNN_TF:
    #if (CONFIG_LIBTENSORFLOW == 1)
        dnn_module->load_model = &ff_dnn_load_model_tf;
        dnn_module->execute_model = &ff_dnn_execute_model_tf;
        dnn_module->free_model = &ff_dnn_free_model_tf;
    #else
        av_freep(&dnn_module);
        return NULL;
    #endif
        break;
    default:
        av_log(NULL, AV_LOG_ERROR, "Module backend_type is not native or tensorflow\n");
        av_freep(&dnn_module);
        return NULL;
    }

    return dnn_module;
}