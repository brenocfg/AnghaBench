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
typedef  int /*<<< orphan*/  curl_mime ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/ * curl_mime_addpart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_mime_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_mime_init (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_mime_subparts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cyclic_add(void)
{
  CURL *easy = curl_easy_init();
  curl_mime *mime = curl_mime_init(easy);
  curl_mimepart *part = curl_mime_addpart(mime);
  CURLcode a1 = curl_mime_subparts(part, mime);

  if(a1 == CURLE_BAD_FUNCTION_ARGUMENT) {
    curl_mime *submime = curl_mime_init(easy);
    curl_mimepart *subpart = curl_mime_addpart(submime);

    curl_mime_subparts(part, submime);
    a1 = curl_mime_subparts(subpart, mime);
  }

  curl_mime_free(mime);
  curl_easy_cleanup(easy);
  if(a1 != CURLE_BAD_FUNCTION_ARGUMENT)
    /* that should have failed */
    return 1;

  return 0;
}