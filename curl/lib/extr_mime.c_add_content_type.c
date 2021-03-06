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
struct curl_slist {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_mime_add_header (struct curl_slist**,char*,char const*,char*,char const*) ; 

__attribute__((used)) static CURLcode add_content_type(struct curl_slist **slp,
                                 const char *type, const char *boundary)
{
  return Curl_mime_add_header(slp, "Content-Type: %s%s%s", type,
                              boundary? "; boundary=": "",
                              boundary? boundary: "");
}