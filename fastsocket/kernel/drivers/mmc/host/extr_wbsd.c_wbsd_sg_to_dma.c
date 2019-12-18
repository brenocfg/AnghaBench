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
struct wbsd_host {char* dma_buffer; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct mmc_data {unsigned int sg_len; struct scatterlist* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 char* sg_virt (struct scatterlist*) ; 

__attribute__((used)) static inline void wbsd_sg_to_dma(struct wbsd_host *host, struct mmc_data *data)
{
	unsigned int len, i;
	struct scatterlist *sg;
	char *dmabuf = host->dma_buffer;
	char *sgbuf;

	sg = data->sg;
	len = data->sg_len;

	for (i = 0; i < len; i++) {
		sgbuf = sg_virt(&sg[i]);
		memcpy(dmabuf, sgbuf, sg[i].length);
		dmabuf += sg[i].length;
	}
}