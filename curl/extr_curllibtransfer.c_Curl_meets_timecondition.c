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
typedef  scalar_t__ time_t ;
struct TYPE_4__ {int timecond; } ;
struct TYPE_3__ {scalar_t__ timevalue; int timecondition; } ;
struct Curl_easy {TYPE_2__ info; TYPE_1__ set; } ;

/* Variables and functions */
#define  CURL_TIMECOND_IFMODSINCE 129 
#define  CURL_TIMECOND_IFUNMODSINCE 128 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 

bool Curl_meets_timecondition(struct Curl_easy *data, time_t timeofdoc)
{
  if((timeofdoc == 0) || (data->set.timevalue == 0))
    return TRUE;

  switch(data->set.timecondition) {
  case CURL_TIMECOND_IFMODSINCE:
  default:
    if(timeofdoc <= data->set.timevalue) {
      infof(data,
            "The requested document is not new enough\n");
      data->info.timecond = TRUE;
      return FALSE;
    }
    break;
  case CURL_TIMECOND_IFUNMODSINCE:
    if(timeofdoc >= data->set.timevalue) {
      infof(data,
            "The requested document is not old enough\n");
      data->info.timecond = TRUE;
      return FALSE;
    }
    break;
  }

  return TRUE;
}