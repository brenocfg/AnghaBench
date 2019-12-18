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
struct ps3vram_priv {int dummy; } ;
struct ps3_system_bus_device {int dummy; } ;

/* Variables and functions */
 int DMA_NOTIFIER_HANDLE_BASE ; 
 int /*<<< orphan*/  DOWNLOAD_SUBCH ; 
 int NOTIFIER ; 
 int /*<<< orphan*/  UPLOAD_SUBCH ; 
 struct ps3vram_priv* ps3_system_bus_get_drvdata (struct ps3_system_bus_device*) ; 
 int /*<<< orphan*/  ps3vram_begin_ring (struct ps3vram_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ps3vram_fire_ring (struct ps3_system_bus_device*) ; 
 int /*<<< orphan*/  ps3vram_out_ring (struct ps3vram_priv*,int) ; 

__attribute__((used)) static void ps3vram_bind(struct ps3_system_bus_device *dev)
{
	struct ps3vram_priv *priv = ps3_system_bus_get_drvdata(dev);

	ps3vram_begin_ring(priv, UPLOAD_SUBCH, 0, 1);
	ps3vram_out_ring(priv, 0x31337303);
	ps3vram_begin_ring(priv, UPLOAD_SUBCH, 0x180, 3);
	ps3vram_out_ring(priv, DMA_NOTIFIER_HANDLE_BASE + NOTIFIER);
	ps3vram_out_ring(priv, 0xfeed0001);	/* DMA system RAM instance */
	ps3vram_out_ring(priv, 0xfeed0000);     /* DMA video RAM instance */

	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH, 0, 1);
	ps3vram_out_ring(priv, 0x3137c0de);
	ps3vram_begin_ring(priv, DOWNLOAD_SUBCH, 0x180, 3);
	ps3vram_out_ring(priv, DMA_NOTIFIER_HANDLE_BASE + NOTIFIER);
	ps3vram_out_ring(priv, 0xfeed0000);	/* DMA video RAM instance */
	ps3vram_out_ring(priv, 0xfeed0001);	/* DMA system RAM instance */

	ps3vram_fire_ring(dev);
}