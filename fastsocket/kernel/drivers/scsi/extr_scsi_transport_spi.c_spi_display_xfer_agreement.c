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
struct spi_transport_attrs {scalar_t__ offset; size_t period; scalar_t__ width; scalar_t__ hold_mcs; scalar_t__ pcomp_en; scalar_t__ wr_flow; scalar_t__ rti; scalar_t__ rd_strm; scalar_t__ qas; scalar_t__ iu; scalar_t__ dt; } ;
struct scsi_target {int /*<<< orphan*/  dev; int /*<<< orphan*/  starget_data; } ;

/* Variables and functions */
 size_t SPI_STATIC_PPR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,...) ; 
 unsigned int* ppr_to_ps ; 
 int /*<<< orphan*/  sprint_frac (char*,unsigned int,int) ; 

void spi_display_xfer_agreement(struct scsi_target *starget)
{
	struct spi_transport_attrs *tp;
	tp = (struct spi_transport_attrs *)&starget->starget_data;

	if (tp->offset > 0 && tp->period > 0) {
		unsigned int picosec, kb100;
		char *scsi = "FAST-?";
		char tmp[8];

		if (tp->period <= SPI_STATIC_PPR) {
			picosec = ppr_to_ps[tp->period];
			switch (tp->period) {
				case  7: scsi = "FAST-320"; break;
				case  8: scsi = "FAST-160"; break;
				case  9: scsi = "FAST-80"; break;
				case 10:
				case 11: scsi = "FAST-40"; break;
				case 12: scsi = "FAST-20"; break;
			}
		} else {
			picosec = tp->period * 4000;
			if (tp->period < 25)
				scsi = "FAST-20";
			else if (tp->period < 50)
				scsi = "FAST-10";
			else
				scsi = "FAST-5";
		}

		kb100 = (10000000 + picosec / 2) / picosec;
		if (tp->width)
			kb100 *= 2;
		sprint_frac(tmp, picosec, 1000);

		dev_info(&starget->dev,
			 "%s %sSCSI %d.%d MB/s %s%s%s%s%s%s%s%s (%s ns, offset %d)\n",
			 scsi, tp->width ? "WIDE " : "", kb100/10, kb100 % 10,
			 tp->dt ? "DT" : "ST",
			 tp->iu ? " IU" : "",
			 tp->qas  ? " QAS" : "",
			 tp->rd_strm ? " RDSTRM" : "",
			 tp->rti ? " RTI" : "",
			 tp->wr_flow ? " WRFLOW" : "",
			 tp->pcomp_en ? " PCOMP" : "",
			 tp->hold_mcs ? " HMCS" : "",
			 tmp, tp->offset);
	} else {
		dev_info(&starget->dev, "%sasynchronous\n",
				tp->width ? "wide " : "");
	}
}