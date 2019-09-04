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
struct TYPE_2__ {int /*<<< orphan*/  flags; scalar_t__ size_dl; } ;
struct Curl_easy {TYPE_1__ progress; } ;
typedef  scalar_t__ curl_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PGRS_DL_SIZE_KNOWN ; 

void Curl_pgrsSetDownloadSize(struct Curl_easy *data, curl_off_t size)
{
  if(size >= 0) {
    data->progress.size_dl = size;
    data->progress.flags |= PGRS_DL_SIZE_KNOWN;
  }
  else {
    data->progress.size_dl = 0;
    data->progress.flags &= ~PGRS_DL_SIZE_KNOWN;
  }
}