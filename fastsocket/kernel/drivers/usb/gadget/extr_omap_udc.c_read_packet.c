#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ actual; scalar_t__ length; } ;
struct omap_req {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_DATA ; 
 scalar_t__ likely (int) ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  omap_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
read_packet(u8 *buf, struct omap_req *req, unsigned avail)
{
	unsigned	len;
	u16		*wp;

	len = min(req->req.length - req->req.actual, avail);
	req->req.actual += len;
	avail = len;

	if (likely((((int)buf) & 1) == 0)) {
		wp = (u16 *)buf;
		while (avail >= 2) {
			*wp++ = omap_readw(UDC_DATA);
			avail -= 2;
		}
		buf = (u8 *)wp;
	}
	while (avail--)
		*buf++ = omap_readb(UDC_DATA);
	return len;
}