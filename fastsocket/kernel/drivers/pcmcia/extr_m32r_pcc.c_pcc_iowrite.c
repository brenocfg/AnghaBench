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

/* Variables and functions */
 int /*<<< orphan*/  pcc_iorw (int,unsigned long,void*,size_t,size_t,int,int) ; 

void pcc_iowrite(int sock, unsigned long port, void *buf, size_t size, size_t nmemb, int flag) {
    pcc_iorw(sock, port, buf, size, nmemb, 1, flag);
}