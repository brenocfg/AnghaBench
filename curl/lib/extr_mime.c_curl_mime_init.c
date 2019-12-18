#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Curl_easy {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * boundary; int /*<<< orphan*/ * lastpart; int /*<<< orphan*/ * firstpart; int /*<<< orphan*/ * parent; struct Curl_easy* easy; } ;
typedef  TYPE_1__ curl_mime ;

/* Variables and functions */
 scalar_t__ Curl_rand_hex (struct Curl_easy*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  MIMESTATE_BEGIN ; 
 scalar_t__ MIME_RAND_BOUNDARY_CHARS ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  mimesetstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

curl_mime *curl_mime_init(struct Curl_easy *easy)
{
  curl_mime *mime;

  mime = (curl_mime *) malloc(sizeof(*mime));

  if(mime) {
    mime->easy = easy;
    mime->parent = NULL;
    mime->firstpart = NULL;
    mime->lastpart = NULL;

    memset(mime->boundary, '-', 24);
    if(Curl_rand_hex(easy, (unsigned char *) &mime->boundary[24],
                     MIME_RAND_BOUNDARY_CHARS + 1)) {
      /* failed to get random separator, bail out */
      free(mime);
      return NULL;
    }
    mimesetstate(&mime->state, MIMESTATE_BEGIN, NULL);
  }

  return mime;
}