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
typedef  size_t u_int ;
struct scb {int dummy; } ;
struct ahc_softc {TYPE_1__* scb_data; } ;
struct TYPE_2__ {struct scb** scbindex; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  ahc_sync_scb (struct ahc_softc*,struct scb*,int) ; 

struct scb *
ahc_lookup_scb(struct ahc_softc *ahc, u_int tag)
{
	struct scb* scb;

	scb = ahc->scb_data->scbindex[tag];
	if (scb != NULL)
		ahc_sync_scb(ahc, scb,
			     BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	return (scb);
}