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
struct s3c2410_udc {int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNABORTED ; 
 unsigned int S3C2410_ENDPOINTS ; 
 int /*<<< orphan*/  s3c2410_udc_nuke (struct s3c2410_udc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s3c2410_udc_clear_ep_state(struct s3c2410_udc *dev)
{
	unsigned i;

	/* hardware SET_{CONFIGURATION,INTERFACE} automagic resets endpoint
	 * fifos, and pending transactions mustn't be continued in any case.
	 */

	for (i = 1; i < S3C2410_ENDPOINTS; i++)
		s3c2410_udc_nuke(dev, &dev->ep[i], -ECONNABORTED);
}