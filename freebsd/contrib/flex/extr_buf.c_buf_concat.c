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
struct Buf {int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_append (struct Buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct Buf *buf_concat(struct Buf* dest, const struct Buf* src)
{
    buf_append(dest, src->elts, src->nelts);
    return dest;
}