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
struct TYPE_5__ {size_t max_processing_chunk; scalar_t__ (* read ) (TYPE_1__*,void*,size_t) ;size_t processed_bytes; int /*<<< orphan*/  (* update_cksum ) (TYPE_1__*,void*,size_t) ;} ;
typedef  TYPE_1__ rio ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__*,void*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,void*,size_t) ; 

__attribute__((used)) static inline size_t rioRead(rio *r, void *buf, size_t len) {
    while (len) {
        size_t bytes_to_read = (r->max_processing_chunk && r->max_processing_chunk < len) ? r->max_processing_chunk : len;
        if (r->read(r,buf,bytes_to_read) == 0)
            return 0;
        if (r->update_cksum) r->update_cksum(r,buf,bytes_to_read);
        buf = (char*)buf + bytes_to_read;
        len -= bytes_to_read;
        r->processed_bytes += bytes_to_read;
    }
    return 1;
}