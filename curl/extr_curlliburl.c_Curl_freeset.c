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
struct TYPE_4__ {int /*<<< orphan*/  mimepost; int /*<<< orphan*/ ** str; } ;
struct TYPE_3__ {int /*<<< orphan*/ * url; void* url_alloc; int /*<<< orphan*/ * referer; void* referer_alloc; } ;
struct Curl_easy {TYPE_2__ set; TYPE_1__ change; } ;
typedef  enum dupstring { ____Placeholder_dupstring } dupstring ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_mime_cleanpart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int STRING_LAST ; 

void Curl_freeset(struct Curl_easy *data)
{
  /* Free all dynamic strings stored in the data->set substructure. */
  enum dupstring i;
  for(i = (enum dupstring)0; i < STRING_LAST; i++) {
    Curl_safefree(data->set.str[i]);
  }

  if(data->change.referer_alloc) {
    Curl_safefree(data->change.referer);
    data->change.referer_alloc = FALSE;
  }
  data->change.referer = NULL;
  if(data->change.url_alloc) {
    Curl_safefree(data->change.url);
    data->change.url_alloc = FALSE;
  }
  data->change.url = NULL;

  Curl_mime_cleanpart(&data->set.mimepost);
}