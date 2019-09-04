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
struct ftp_parselist_data {int /*<<< orphan*/  file_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_fileinfo_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ftp_parselist_data*) ; 

void Curl_ftp_parselist_data_free(struct ftp_parselist_data **parserp)
{
  struct ftp_parselist_data *parser = *parserp;
  if(parser)
    Curl_fileinfo_cleanup(parser->file_data);
  free(parser);
  *parserp = NULL;
}