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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int title_count; int preview_count; scalar_t__ progress; scalar_t__ preview_cur; scalar_t__ title_cur; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_STATE_SCANNING ; 
 int /*<<< orphan*/  h_scan ; 
 int /*<<< orphan*/  hb_scan (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ hb_status ; 

void
ghb_backend_scan(const gchar *path, gint titleindex, gint preview_count, uint64_t min_duration)
{
    hb_scan( h_scan, path, titleindex, preview_count, 1, min_duration );
    hb_status.scan.state |= GHB_STATE_SCANNING;
    // initialize count and cur to something that won't cause FPE
    // when computing progress
    hb_status.scan.title_count = 1;
    hb_status.scan.title_cur = 0;
    hb_status.scan.preview_count = 1;
    hb_status.scan.preview_cur = 0;
    hb_status.scan.progress = 0;
}