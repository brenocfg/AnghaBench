#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {long length; int /*<<< orphan*/  data_deallocator; void* data; } ;
typedef  TYPE_1__ TF_Buffer ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 TYPE_1__* TF_NewBuffer () ; 
 int /*<<< orphan*/  av_freep (unsigned char**) ; 
 unsigned char* av_malloc (long) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ **) ; 
 scalar_t__ avio_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 long avio_read (int /*<<< orphan*/ *,unsigned char*,long) ; 
 long avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_buffer ; 

__attribute__((used)) static TF_Buffer *read_graph(const char *model_filename)
{
    TF_Buffer *graph_buf;
    unsigned char *graph_data = NULL;
    AVIOContext *model_file_context;
    long size, bytes_read;

    if (avio_open(&model_file_context, model_filename, AVIO_FLAG_READ) < 0){
        return NULL;
    }

    size = avio_size(model_file_context);

    graph_data = av_malloc(size);
    if (!graph_data){
        avio_closep(&model_file_context);
        return NULL;
    }
    bytes_read = avio_read(model_file_context, graph_data, size);
    avio_closep(&model_file_context);
    if (bytes_read != size){
        av_freep(&graph_data);
        return NULL;
    }

    graph_buf = TF_NewBuffer();
    graph_buf->data = (void *)graph_data;
    graph_buf->length = size;
    graph_buf->data_deallocator = free_buffer;

    return graph_buf;
}