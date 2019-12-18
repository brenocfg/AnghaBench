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
struct TYPE_2__ {int flags; int /*<<< orphan*/  t_redirect; scalar_t__ size_ul; scalar_t__ size_dl; scalar_t__ ulspeed; scalar_t__ dlspeed; scalar_t__ downloaded; scalar_t__ uploaded; int /*<<< orphan*/  t_starttransfer; int /*<<< orphan*/  t_pretransfer; int /*<<< orphan*/  t_appconnect; int /*<<< orphan*/  t_connect; int /*<<< orphan*/  t_nslookup; int /*<<< orphan*/  timespent; } ;
struct Curl_easy {TYPE_1__ progress; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int CURLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNKNOWN_OPTION ; 
#define  CURLINFO_APPCONNECT_TIME 140 
#define  CURLINFO_CONNECT_TIME 139 
#define  CURLINFO_CONTENT_LENGTH_DOWNLOAD 138 
#define  CURLINFO_CONTENT_LENGTH_UPLOAD 137 
#define  CURLINFO_NAMELOOKUP_TIME 136 
#define  CURLINFO_PRETRANSFER_TIME 135 
#define  CURLINFO_REDIRECT_TIME 134 
#define  CURLINFO_SIZE_DOWNLOAD 133 
#define  CURLINFO_SIZE_UPLOAD 132 
#define  CURLINFO_SPEED_DOWNLOAD 131 
#define  CURLINFO_SPEED_UPLOAD 130 
#define  CURLINFO_STARTTRANSFER_TIME 129 
#define  CURLINFO_TOTAL_TIME 128 
 double DOUBLE_SECS (int /*<<< orphan*/ ) ; 
 int PGRS_DL_SIZE_KNOWN ; 
 int PGRS_UL_SIZE_KNOWN ; 

__attribute__((used)) static CURLcode getinfo_double(struct Curl_easy *data, CURLINFO info,
                               double *param_doublep)
{
  switch(info) {
  case CURLINFO_TOTAL_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.timespent);
    break;
  case CURLINFO_NAMELOOKUP_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.t_nslookup);
    break;
  case CURLINFO_CONNECT_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.t_connect);
    break;
  case CURLINFO_APPCONNECT_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.t_appconnect);
    break;
  case CURLINFO_PRETRANSFER_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.t_pretransfer);
    break;
  case CURLINFO_STARTTRANSFER_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.t_starttransfer);
    break;
  case CURLINFO_SIZE_UPLOAD:
    *param_doublep =  (double)data->progress.uploaded;
    break;
  case CURLINFO_SIZE_DOWNLOAD:
    *param_doublep = (double)data->progress.downloaded;
    break;
  case CURLINFO_SPEED_DOWNLOAD:
    *param_doublep =  (double)data->progress.dlspeed;
    break;
  case CURLINFO_SPEED_UPLOAD:
    *param_doublep = (double)data->progress.ulspeed;
    break;
  case CURLINFO_CONTENT_LENGTH_DOWNLOAD:
    *param_doublep = (data->progress.flags & PGRS_DL_SIZE_KNOWN)?
      (double)data->progress.size_dl:-1;
    break;
  case CURLINFO_CONTENT_LENGTH_UPLOAD:
    *param_doublep = (data->progress.flags & PGRS_UL_SIZE_KNOWN)?
      (double)data->progress.size_ul:-1;
    break;
  case CURLINFO_REDIRECT_TIME:
    *param_doublep = DOUBLE_SECS(data->progress.t_redirect);
    break;

  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}