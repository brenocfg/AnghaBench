#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ name; } ;
typedef  TYPE_1__ mime_encoder ;
struct TYPE_6__ {TYPE_1__ const* encoder; } ;
typedef  TYPE_2__ curl_mimepart ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 TYPE_1__* encoders ; 
 scalar_t__ strcasecompare (char const*,scalar_t__) ; 

CURLcode curl_mime_encoder(curl_mimepart *part, const char *encoding)
{
  CURLcode result = CURLE_BAD_FUNCTION_ARGUMENT;
  const mime_encoder *mep;

  if(!part)
    return result;

  part->encoder = NULL;

  if(!encoding)
    return CURLE_OK;    /* Removing current encoder. */

  for(mep = encoders; mep->name; mep++)
    if(strcasecompare(encoding, mep->name)) {
      part->encoder = mep;
      result = CURLE_OK;
    }

  return result;
}