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
struct TYPE_2__ {char* in; scalar_t__ ucode; int /*<<< orphan*/  getflags; int /*<<< orphan*/  out; int /*<<< orphan*/  urlflags; } ;
typedef  scalar_t__ CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUPART_URL ; 
 scalar_t__ checkparts (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,scalar_t__) ; 
 TYPE_1__* get_parts_list ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int get_parts(void)
{
  int i;
  int error = 0;
  for(i = 0; get_parts_list[i].in && !error; i++) {
    CURLUcode rc;
    CURLU *urlp = curl_url();
    if(!urlp) {
      error++;
      break;
    }
    rc = curl_url_set(urlp, CURLUPART_URL,
                      get_parts_list[i].in,
                      get_parts_list[i].urlflags);
    if(rc != get_parts_list[i].ucode) {
      fprintf(stderr, "Get parts\nin: %s\nreturned %d (expected %d)\n",
              get_parts_list[i].in, (int)rc, get_parts_list[i].ucode);
      error++;
    }
    else if(get_parts_list[i].ucode) {
      /* the expected error happened */
    }
    else if(checkparts(urlp, get_parts_list[i].in, get_parts_list[i].out,
                       get_parts_list[i].getflags))
      error++;
    curl_url_cleanup(urlp);
  }
  return error;
}