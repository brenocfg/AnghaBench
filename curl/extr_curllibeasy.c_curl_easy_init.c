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
struct Curl_easy {int dummy; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 scalar_t__ Curl_open (struct Curl_easy**) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  stderr ; 

struct Curl_easy *curl_easy_init(void)
{
  CURLcode result;
  struct Curl_easy *data;

  /* Make sure we inited the global SSL stuff */
  if(!initialized) {
    result = curl_global_init(CURL_GLOBAL_DEFAULT);
    if(result) {
      /* something in the global init failed, return nothing */
      DEBUGF(fprintf(stderr, "Error: curl_global_init failed\n"));
      return NULL;
    }
  }

  /* We use curl_open() with undefined URL so far */
  result = Curl_open(&data);
  if(result) {
    DEBUGF(fprintf(stderr, "Error: Curl_open failed\n"));
    return NULL;
  }

  return data;
}