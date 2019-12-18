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
struct TYPE_2__ {int /*<<< orphan*/  t_starttransfer; int /*<<< orphan*/  t_pretransfer; int /*<<< orphan*/  t_appconnect; int /*<<< orphan*/  t_connect; int /*<<< orphan*/  t_nslookup; } ;
struct Curl_easy {TYPE_1__ progress; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  fail_unless (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  usec_matches_seconds (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void expect_timer_seconds(struct Curl_easy *data, int seconds)
{
  char msg[64];
  msnprintf(msg, sizeof(msg), "about %d seconds should have passed", seconds);
  fail_unless(usec_matches_seconds(data->progress.t_nslookup, seconds), msg);
  fail_unless(usec_matches_seconds(data->progress.t_connect, seconds), msg);
  fail_unless(usec_matches_seconds(data->progress.t_appconnect, seconds), msg);
  fail_unless(usec_matches_seconds(data->progress.t_pretransfer, seconds),
              msg);
  fail_unless(usec_matches_seconds(data->progress.t_starttransfer, seconds),
              msg);
}