#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_4__ {int flags; scalar_t__ speeder_c; int /*<<< orphan*/  callback; scalar_t__ lastshow; } ;
struct TYPE_3__ {int /*<<< orphan*/  err; } ;
struct Curl_easy {TYPE_2__ progress; TYPE_1__ set; } ;

/* Variables and functions */
 int Curl_pgrsUpdate (struct connectdata*) ; 
 int PGRS_HIDE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 

int Curl_pgrsDone(struct connectdata *conn)
{
  int rc;
  struct Curl_easy *data = conn->data;
  data->progress.lastshow = 0;
  rc = Curl_pgrsUpdate(conn); /* the final (forced) update */
  if(rc)
    return rc;

  if(!(data->progress.flags & PGRS_HIDE) &&
     !data->progress.callback)
    /* only output if we don't use a progress callback and we're not
     * hidden */
    fprintf(data->set.err, "\n");

  data->progress.speeder_c = 0; /* reset the progress meter display */
  return 0;
}