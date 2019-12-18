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
struct connectdata {int multiuse; struct connectdata* multi; struct connectdata* data; struct connectdata* bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGASSERT (struct connectdata*) ; 
 int /*<<< orphan*/  process_pending_handles (struct connectdata*) ; 

void Curl_multiuse_state(struct connectdata *conn,
                         int bundlestate) /* use BUNDLE_* defines */
{
  DEBUGASSERT(conn);
  DEBUGASSERT(conn->bundle);
  DEBUGASSERT(conn->data);
  DEBUGASSERT(conn->data->multi);

  conn->bundle->multiuse = bundlestate;
  process_pending_handles(conn->data->multi);
}