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
struct curl_httppost {int dummy; } ;
typedef  int /*<<< orphan*/  curl_formget_callback ;
struct TYPE_2__ {unsigned int ccsid; void* arg; int /*<<< orphan*/  append; } ;
typedef  TYPE_1__ cfcdata ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_formget_callback_ccsid ; 
 int curl_formget (struct curl_httppost*,void*,int /*<<< orphan*/ ) ; 

int
curl_formget_ccsid(struct curl_httppost *form, void *arg,
                   curl_formget_callback append, unsigned int ccsid)

{
  cfcdata lcfc;

  lcfc.append = append;
  lcfc.arg = arg;
  lcfc.ccsid = ccsid;
  return curl_formget(form, (void *) &lcfc, Curl_formget_callback_ccsid);
}