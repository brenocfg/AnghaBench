#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {int is_t_startransfer_set; int flags; int /*<<< orphan*/  start; scalar_t__ uploaded; scalar_t__ downloaded; TYPE_2__ dl_limit_start; TYPE_1__ ul_limit_start; scalar_t__ speeder_c; } ;
struct Curl_easy {TYPE_3__ progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  Curl_ratelimit (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int PGRS_HEADERS_OUT ; 
 int PGRS_HIDE ; 

void Curl_pgrsStartNow(struct Curl_easy *data)
{
  data->progress.speeder_c = 0; /* reset the progress meter display */
  data->progress.start = Curl_now();
  data->progress.is_t_startransfer_set = false;
  data->progress.ul_limit_start.tv_sec = 0;
  data->progress.ul_limit_start.tv_usec = 0;
  data->progress.dl_limit_start.tv_sec = 0;
  data->progress.dl_limit_start.tv_usec = 0;
  data->progress.downloaded = 0;
  data->progress.uploaded = 0;
  /* clear all bits except HIDE and HEADERS_OUT */
  data->progress.flags &= PGRS_HIDE|PGRS_HEADERS_OUT;
  Curl_ratelimit(data, data->progress.start);
}