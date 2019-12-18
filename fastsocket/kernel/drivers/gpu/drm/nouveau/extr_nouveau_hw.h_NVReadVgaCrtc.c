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
typedef  int /*<<< orphan*/  uint8_t ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NV_PRMCIO_CRX__COLOR ; 
 scalar_t__ NV_PRMCIO_CR__COLOR ; 
 int NV_PRMCIO_SIZE ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int /*<<< orphan*/  nv_rd08 (struct nouveau_device*,scalar_t__) ; 
 int /*<<< orphan*/  nv_wr08 (struct nouveau_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t NVReadVgaCrtc(struct drm_device *dev,
					int head, uint8_t index)
{
	struct nouveau_device *device = nouveau_dev(dev);
	uint8_t val;
	nv_wr08(device, NV_PRMCIO_CRX__COLOR + head * NV_PRMCIO_SIZE, index);
	val = nv_rd08(device, NV_PRMCIO_CR__COLOR + head * NV_PRMCIO_SIZE);
	return val;
}