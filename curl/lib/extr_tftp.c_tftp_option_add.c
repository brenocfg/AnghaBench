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
struct TYPE_3__ {scalar_t__ blksize; } ;
typedef  TYPE_1__ tftp_state_data_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_TFTP_ILLEGAL ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static CURLcode tftp_option_add(tftp_state_data_t *state, size_t *csize,
                                char *buf, const char *option)
{
  if(( strlen(option) + *csize + 1) > (size_t)state->blksize)
    return CURLE_TFTP_ILLEGAL;
  strcpy(buf, option);
  *csize += strlen(option) + 1;
  return CURLE_OK;
}