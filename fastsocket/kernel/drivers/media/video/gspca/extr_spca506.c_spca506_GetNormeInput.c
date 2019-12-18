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
struct sd {int /*<<< orphan*/  channel; int /*<<< orphan*/  norme; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spca506_GetNormeInput(struct gspca_dev *gspca_dev,
				  __u16 *norme, __u16 *channel)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* Read the register is not so good value change so
	   we use your own copy in spca50x struct */
	*norme = sd->norme;
	*channel = sd->channel;
	PDEBUG(D_STREAM, "Get Norme: %d Channel %d", *norme, *channel);
}