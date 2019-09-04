#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* prot; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_6__ {int (* url_get_multi_file_handle ) (TYPE_2__*,int**,int*) ;int (* url_get_file_handle ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int* av_malloc (int) ; 
 int stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*,int**,int*) ; 

int ffurl_get_multi_file_handle(URLContext *h, int **handles, int *numhandles)
{
    if (!h || !h->prot)
        return AVERROR(ENOSYS);
    if (!h->prot->url_get_multi_file_handle) {
        if (!h->prot->url_get_file_handle)
            return AVERROR(ENOSYS);
        *handles = av_malloc(sizeof(**handles));
        if (!*handles)
            return AVERROR(ENOMEM);
        *numhandles = 1;
        *handles[0] = h->prot->url_get_file_handle(h);
        return 0;
    }
    return h->prot->url_get_multi_file_handle(h, handles, numhandles);
}