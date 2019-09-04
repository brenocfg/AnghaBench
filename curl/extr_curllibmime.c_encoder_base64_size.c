#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int curl_off_t ;
struct TYPE_3__ {int datasize; } ;
typedef  TYPE_1__ curl_mimepart ;

/* Variables and functions */
 int MAX_ENCODED_LINE_LENGTH ; 

__attribute__((used)) static curl_off_t encoder_base64_size(curl_mimepart *part)
{
  curl_off_t size = part->datasize;

  if(size <= 0)
    return size;    /* Unknown size or no data. */

  /* Compute base64 character count. */
  size = 4 * (1 + (size - 1) / 3);

  /* Effective character count must include CRLFs. */
  return size + 2 * ((size - 1) / MAX_ENCODED_LINE_LENGTH);
}