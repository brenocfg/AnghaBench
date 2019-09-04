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
struct ftp_parselist_data {int dummy; } ;

/* Variables and functions */
 struct ftp_parselist_data* calloc (int,int) ; 

struct ftp_parselist_data *Curl_ftp_parselist_data_alloc(void)
{
  return calloc(1, sizeof(struct ftp_parselist_data));
}