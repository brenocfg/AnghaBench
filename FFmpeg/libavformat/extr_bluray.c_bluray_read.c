#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  bd; } ;
typedef  TYPE_2__ BlurayContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EFAULT ; 
 int bd_read (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int bluray_read(URLContext *h, unsigned char *buf, int size)
{
    BlurayContext *bd = h->priv_data;
    int len;

    if (!bd || !bd->bd) {
        return AVERROR(EFAULT);
    }

    len = bd_read(bd->bd, buf, size);

    return len == 0 ? AVERROR_EOF : len;
}