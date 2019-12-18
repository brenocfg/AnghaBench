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
typedef  int u32 ;
struct rsvp_head {scalar_t__ tgenerator; } ;

/* Variables and functions */
 scalar_t__ tunnel_bts (struct rsvp_head*) ; 
 int /*<<< orphan*/  tunnel_recycle (struct rsvp_head*) ; 

__attribute__((used)) static u32 gen_tunnel(struct rsvp_head *data)
{
	int i, k;

	for (k=0; k<2; k++) {
		for (i=255; i>0; i--) {
			if (++data->tgenerator == 0)
				data->tgenerator = 1;
			if (tunnel_bts(data))
				return data->tgenerator;
		}
		tunnel_recycle(data);
	}
	return 0;
}