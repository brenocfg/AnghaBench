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
struct scsi_host_template {int dummy; } ;
struct aic7xxx_host {int /*<<< orphan*/  host_no; int /*<<< orphan*/  base; TYPE_1__* scb_data; struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  scb_data_type ;
struct TYPE_2__ {int /*<<< orphan*/  free_scbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAXREG ; 
 scalar_t__ MINREG ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aic7xxx_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scbq_init (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_register (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_unregister (struct Scsi_Host*) ; 

__attribute__((used)) static struct aic7xxx_host *
aic7xxx_alloc(struct scsi_host_template *sht, struct aic7xxx_host *temp)
{
  struct aic7xxx_host *p = NULL;
  struct Scsi_Host *host;

  /*
   * Allocate a storage area by registering us with the mid-level
   * SCSI layer.
   */
  host = scsi_register(sht, sizeof(struct aic7xxx_host));

  if (host != NULL)
  {
    p = (struct aic7xxx_host *) host->hostdata;
    memset(p, 0, sizeof(struct aic7xxx_host));
    *p = *temp;
    p->host = host;

    p->scb_data = kzalloc(sizeof(scb_data_type), GFP_ATOMIC);
    if (p->scb_data)
    {
      scbq_init (&p->scb_data->free_scbs);
    }
    else
    {
      /*
       * For some reason we don't have enough memory.  Free the
       * allocated memory for the aic7xxx_host struct, and return NULL.
       */
      release_region(p->base, MAXREG - MINREG);
      scsi_unregister(host);
      return(NULL);
    }
    p->host_no = host->host_no;
  }
  return (p);
}