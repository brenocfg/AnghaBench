#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  graph; } ;
typedef  int /*<<< orphan*/  TF_ImportGraphDefOptions ;
typedef  int /*<<< orphan*/  TF_Buffer ;
typedef  TYPE_1__ TFModel ;
typedef  int /*<<< orphan*/  DNNReturnType ;

/* Variables and functions */
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int /*<<< orphan*/  TF_DeleteBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF_DeleteGraph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_DeleteImportGraphDefOptions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF_DeleteStatus (int /*<<< orphan*/ ) ; 
 scalar_t__ TF_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_GraphImportGraphDef (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_NewGraph () ; 
 int /*<<< orphan*/ * TF_NewImportGraphDefOptions () ; 
 int /*<<< orphan*/  TF_NewStatus () ; 
 scalar_t__ TF_OK ; 
 int /*<<< orphan*/ * read_graph (char const*) ; 

__attribute__((used)) static DNNReturnType load_tf_model(TFModel *tf_model, const char *model_filename)
{
    TF_Buffer *graph_def;
    TF_ImportGraphDefOptions *graph_opts;

    graph_def = read_graph(model_filename);
    if (!graph_def){
        return DNN_ERROR;
    }
    tf_model->graph = TF_NewGraph();
    tf_model->status = TF_NewStatus();
    graph_opts = TF_NewImportGraphDefOptions();
    TF_GraphImportGraphDef(tf_model->graph, graph_def, graph_opts, tf_model->status);
    TF_DeleteImportGraphDefOptions(graph_opts);
    TF_DeleteBuffer(graph_def);
    if (TF_GetCode(tf_model->status) != TF_OK){
        TF_DeleteGraph(tf_model->graph);
        TF_DeleteStatus(tf_model->status);
        return DNN_ERROR;
    }

    return DNN_SUCCESS;
}