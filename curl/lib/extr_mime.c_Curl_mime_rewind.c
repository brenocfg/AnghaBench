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
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_SEND_FAIL_REWIND ; 
 scalar_t__ CURL_SEEKFUNC_OK ; 
 scalar_t__ mime_part_rewind (int /*<<< orphan*/ *) ; 

CURLcode Curl_mime_rewind(curl_mimepart *part)
{
  return mime_part_rewind(part) == CURL_SEEKFUNC_OK?
         CURLE_OK: CURLE_SEND_FAIL_REWIND;
}