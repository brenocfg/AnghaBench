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

/* Variables and functions */
 int /*<<< orphan*/  Curl_pgrsSetDownloadSize (struct Curl_easy*,int) ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadSize (struct Curl_easy*,int) ; 

void Curl_pgrsResetTransferSizes(struct Curl_easy *data)
{
  Curl_pgrsSetDownloadSize(data, -1);
  Curl_pgrsSetUploadSize(data, -1);
}