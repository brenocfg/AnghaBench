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
struct connectdata {int /*<<< orphan*/  data; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_ABORTED_BY_CALLBACK ; 
 int /*<<< orphan*/  Curl_now () ; 
 scalar_t__ Curl_pgrsUpdate (struct connectdata*) ; 
 scalar_t__ Curl_speedcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tftp_multi_statemach (struct connectdata*,int*) ; 

__attribute__((used)) static CURLcode tftp_doing(struct connectdata *conn, bool *dophase_done)
{
  CURLcode result;
  result = tftp_multi_statemach(conn, dophase_done);

  if(*dophase_done) {
    DEBUGF(infof(conn->data, "DO phase is complete\n"));
  }
  else if(!result) {
    /* The multi code doesn't have this logic for the DOING state so we
       provide it for TFTP since it may do the entire transfer in this
       state. */
    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else
      result = Curl_speedcheck(conn->data, Curl_now());
  }
  return result;
}