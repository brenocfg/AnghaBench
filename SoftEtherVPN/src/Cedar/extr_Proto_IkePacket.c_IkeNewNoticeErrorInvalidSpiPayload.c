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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  Endian32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IKE_NOTICE_ERROR_INVALID_SPI ; 
 int /*<<< orphan*/  IKE_PROTOCOL_ID_IPSEC_ESP ; 
 int /*<<< orphan*/ * IkeNewNoticePayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

IKE_PACKET_PAYLOAD *IkeNewNoticeErrorInvalidSpiPayload(UINT spi)
{
	IKE_PACKET_PAYLOAD *ret;
	spi = Endian32(spi);

	ret = IkeNewNoticePayload(IKE_PROTOCOL_ID_IPSEC_ESP, IKE_NOTICE_ERROR_INVALID_SPI, &spi, sizeof(UINT),
		&spi, sizeof(UINT));

	return ret;
}