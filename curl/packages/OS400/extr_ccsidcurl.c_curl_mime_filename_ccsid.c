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
 int /*<<< orphan*/  curl_mime_filename ; 
 int /*<<< orphan*/  mime_string_call (int /*<<< orphan*/ *,char const*,unsigned int,int /*<<< orphan*/ ) ; 

CURLcode
curl_mime_filename_ccsid(curl_mimepart *part,
                         const char *filename, unsigned int ccsid)

{
  return mime_string_call(part, filename, ccsid, curl_mime_filename);
}