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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int PBUFSIZ ; 
 int last_sent_signal ; 
 int last_sent_step ; 
 int /*<<< orphan*/  sds_send (unsigned char*,int) ; 

__attribute__((used)) static void
sds_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  unsigned char buf[PBUFSIZ];

  last_sent_signal = siggnal;
  last_sent_step = step;

  buf[0] = (step ? 21 : 20);
  buf[1] = 0;			/* (should be signal?) */

  sds_send (buf, 2);
}