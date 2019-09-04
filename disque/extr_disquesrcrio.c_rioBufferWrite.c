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
struct TYPE_5__ {size_t pos; int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {TYPE_1__ buffer; } ;
struct TYPE_7__ {TYPE_2__ io; } ;
typedef  TYPE_3__ rio ;

/* Variables and functions */
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static size_t rioBufferWrite(rio *r, const void *buf, size_t len) {
    r->io.buffer.ptr = sdscatlen(r->io.buffer.ptr,(char*)buf,len);
    r->io.buffer.pos += len;
    return 1;
}