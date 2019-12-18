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
typedef  int /*<<< orphan*/  zimg_image_format ;
typedef  int /*<<< orphan*/  zimg_graph_builder_params ;
typedef  int /*<<< orphan*/  zimg_filter_graph ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_malloc (size_t) ; 
 int print_zimg_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zimg_filter_graph_build (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zimg_filter_graph_free (int /*<<< orphan*/ *) ; 
 int zimg_filter_graph_get_tmp_size (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int graph_build(zimg_filter_graph **graph, zimg_graph_builder_params *params,
                       zimg_image_format *src_format, zimg_image_format *dst_format,
                       void **tmp, size_t *tmp_size)
{
    int ret;
    size_t size;

    zimg_filter_graph_free(*graph);
    *graph = zimg_filter_graph_build(src_format, dst_format, params);
    if (!*graph)
        return print_zimg_error(NULL);

    ret = zimg_filter_graph_get_tmp_size(*graph, &size);
    if (ret)
        return print_zimg_error(NULL);

    if (size > *tmp_size) {
        av_freep(tmp);
        *tmp = av_malloc(size);
        if (!*tmp)
            return AVERROR(ENOMEM);

        *tmp_size = size;
    }

    return 0;
}