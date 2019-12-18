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
struct TYPE_3__ {void* (* create ) (void**) ;} ;
typedef  TYPE_1__ mz_stream_vtbl ;

/* Variables and functions */
 void* stub1 (void**) ; 

void *mz_stream_create(void **stream, mz_stream_vtbl *vtbl)
{
    if (stream == NULL)
        return NULL;
    if (vtbl == NULL || vtbl->create == NULL)
        return NULL;
    return vtbl->create(stream);
}