#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_i2c_bus_rec {int valid; } ;
struct radeon_hpd {void* hpd; } ;
struct TYPE_4__ {int connector_table; } ;
struct radeon_device {int flags; TYPE_2__ mode_info; int /*<<< orphan*/  family; TYPE_1__* pdev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_3__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_RN50 (struct radeon_device*) ; 
 int ATOM_DEVICE_CRT1_SUPPORT ; 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
 int ATOM_DEVICE_DFP1_SUPPORT ; 
 int ATOM_DEVICE_DFP2_SUPPORT ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_TV1_SUPPORT ; 
 int /*<<< orphan*/  CHIP_R100 ; 
 int /*<<< orphan*/  CHIP_R200 ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_LVDS ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_SVIDEO ; 
 int /*<<< orphan*/  CONNECTOR_OBJECT_ID_VGA ; 
#define  CT_EMAC 141 
#define  CT_GENERIC 140 
#define  CT_IBOOK 139 
#define  CT_IMAC_G5_ISIGHT 138 
#define  CT_MAC_G4_SILVER 137 
#define  CT_MAC_G5_9600 136 
#define  CT_MAC_X800 135 
#define  CT_MINI_EXTERNAL 134 
#define  CT_MINI_INTERNAL 133 
 int CT_NONE ; 
#define  CT_POWERBOOK_EXTERNAL 132 
#define  CT_POWERBOOK_INTERNAL 131 
#define  CT_POWERBOOK_VGA 130 
#define  CT_RN50_POWER 129 
#define  CT_SAM440EP 128 
 int /*<<< orphan*/  DDC_CRT2 ; 
 int /*<<< orphan*/  DDC_DVI ; 
 int /*<<< orphan*/  DDC_MONID ; 
 int /*<<< orphan*/  DDC_NONE_DETECTED ; 
 int /*<<< orphan*/  DDC_VGA ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVID ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVII ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_SVIDEO ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 void* RADEON_HPD_1 ; 
 void* RADEON_HPD_2 ; 
 void* RADEON_HPD_NONE ; 
 int RADEON_IS_MOBILITY ; 
 int RADEON_SINGLE_CRTC ; 
 struct radeon_i2c_bus_rec combios_setup_i2c_bus (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  radeon_add_legacy_connector (struct drm_device*,int,int,int /*<<< orphan*/ ,struct radeon_i2c_bus_rec*,int /*<<< orphan*/ ,struct radeon_hpd*) ; 
 int /*<<< orphan*/  radeon_add_legacy_encoder (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int radeon_connector_table ; 
 int /*<<< orphan*/  radeon_get_encoder_enum (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  radeon_link_encoder_connector (struct drm_device*) ; 

bool radeon_get_legacy_connector_info_from_table(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_i2c_bus_rec ddc_i2c;
	struct radeon_hpd hpd;

	rdev->mode_info.connector_table = radeon_connector_table;
	if (rdev->mode_info.connector_table == CT_NONE) {
#ifdef CONFIG_PPC_PMAC
		if (of_machine_is_compatible("PowerBook3,3")) {
			/* powerbook with VGA */
			rdev->mode_info.connector_table = CT_POWERBOOK_VGA;
		} else if (of_machine_is_compatible("PowerBook3,4") ||
			   of_machine_is_compatible("PowerBook3,5")) {
			/* powerbook with internal tmds */
			rdev->mode_info.connector_table = CT_POWERBOOK_INTERNAL;
		} else if (of_machine_is_compatible("PowerBook5,1") ||
			   of_machine_is_compatible("PowerBook5,2") ||
			   of_machine_is_compatible("PowerBook5,3") ||
			   of_machine_is_compatible("PowerBook5,4") ||
			   of_machine_is_compatible("PowerBook5,5")) {
			/* powerbook with external single link tmds (sil164) */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		} else if (of_machine_is_compatible("PowerBook5,6")) {
			/* powerbook with external dual or single link tmds */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		} else if (of_machine_is_compatible("PowerBook5,7") ||
			   of_machine_is_compatible("PowerBook5,8") ||
			   of_machine_is_compatible("PowerBook5,9")) {
			/* PowerBook6,2 ? */
			/* powerbook with external dual link tmds (sil1178?) */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		} else if (of_machine_is_compatible("PowerBook4,1") ||
			   of_machine_is_compatible("PowerBook4,2") ||
			   of_machine_is_compatible("PowerBook4,3") ||
			   of_machine_is_compatible("PowerBook6,3") ||
			   of_machine_is_compatible("PowerBook6,5") ||
			   of_machine_is_compatible("PowerBook6,7")) {
			/* ibook */
			rdev->mode_info.connector_table = CT_IBOOK;
		} else if (of_machine_is_compatible("PowerMac3,5")) {
			/* PowerMac G4 Silver radeon 7500 */
			rdev->mode_info.connector_table = CT_MAC_G4_SILVER;
		} else if (of_machine_is_compatible("PowerMac4,4")) {
			/* emac */
			rdev->mode_info.connector_table = CT_EMAC;
		} else if (of_machine_is_compatible("PowerMac10,1")) {
			/* mini with internal tmds */
			rdev->mode_info.connector_table = CT_MINI_INTERNAL;
		} else if (of_machine_is_compatible("PowerMac10,2")) {
			/* mini with external tmds */
			rdev->mode_info.connector_table = CT_MINI_EXTERNAL;
		} else if (of_machine_is_compatible("PowerMac12,1")) {
			/* PowerMac8,1 ? */
			/* imac g5 isight */
			rdev->mode_info.connector_table = CT_IMAC_G5_ISIGHT;
		} else if ((rdev->pdev->device == 0x4a48) &&
			   (rdev->pdev->subsystem_vendor == 0x1002) &&
			   (rdev->pdev->subsystem_device == 0x4a48)) {
			/* Mac X800 */
			rdev->mode_info.connector_table = CT_MAC_X800;
		} else if ((of_machine_is_compatible("PowerMac7,2") ||
			    of_machine_is_compatible("PowerMac7,3")) &&
			   (rdev->pdev->device == 0x4150) &&
			   (rdev->pdev->subsystem_vendor == 0x1002) &&
			   (rdev->pdev->subsystem_device == 0x4150)) {
			/* Mac G5 tower 9600 */
			rdev->mode_info.connector_table = CT_MAC_G5_9600;
		} else if ((rdev->pdev->device == 0x4c66) &&
			   (rdev->pdev->subsystem_vendor == 0x1002) &&
			   (rdev->pdev->subsystem_device == 0x4c66)) {
			/* SAM440ep RV250 embedded board */
			rdev->mode_info.connector_table = CT_SAM440EP;
		} else
#endif /* CONFIG_PPC_PMAC */
#ifdef CONFIG_PPC64
		if (ASIC_IS_RN50(rdev))
			rdev->mode_info.connector_table = CT_RN50_POWER;
		else
#endif
			rdev->mode_info.connector_table = CT_GENERIC;
	}

	switch (rdev->mode_info.connector_table) {
	case CT_GENERIC:
		DRM_INFO("Connector Table: %d (generic)\n",
			 rdev->mode_info.connector_table);
		/* these are the most common settings */
		if (rdev->flags & RADEON_SINGLE_CRTC) {
			/* VGA - primary dac */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_connector(dev, 0,
						    ATOM_DEVICE_CRT1_SUPPORT,
						    DRM_MODE_CONNECTOR_VGA,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_VGA,
						    &hpd);
		} else if (rdev->flags & RADEON_IS_MOBILITY) {
			/* LVDS */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_NONE_DETECTED, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_LCD1_SUPPORT,
									0),
						  ATOM_DEVICE_LCD1_SUPPORT);
			radeon_add_legacy_connector(dev, 0,
						    ATOM_DEVICE_LCD1_SUPPORT,
						    DRM_MODE_CONNECTOR_LVDS,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_LVDS,
						    &hpd);

			/* VGA - primary dac */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_connector(dev, 1,
						    ATOM_DEVICE_CRT1_SUPPORT,
						    DRM_MODE_CONNECTOR_VGA,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_VGA,
						    &hpd);
		} else {
			/* DVI-I - tv dac, int tmds */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
			hpd.hpd = RADEON_HPD_1;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_DFP1_SUPPORT,
									0),
						  ATOM_DEVICE_DFP1_SUPPORT);
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_CRT2_SUPPORT,
									2),
						  ATOM_DEVICE_CRT2_SUPPORT);
			radeon_add_legacy_connector(dev, 0,
						    ATOM_DEVICE_DFP1_SUPPORT |
						    ATOM_DEVICE_CRT2_SUPPORT,
						    DRM_MODE_CONNECTOR_DVII,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
						    &hpd);

			/* VGA - primary dac */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_connector(dev, 1,
						    ATOM_DEVICE_CRT1_SUPPORT,
						    DRM_MODE_CONNECTOR_VGA,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_VGA,
						    &hpd);
		}

		if (rdev->family != CHIP_R100 && rdev->family != CHIP_R200) {
			/* TV - tv dac */
			ddc_i2c.valid = false;
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_enum(dev,
									ATOM_DEVICE_TV1_SUPPORT,
									2),
						  ATOM_DEVICE_TV1_SUPPORT);
			radeon_add_legacy_connector(dev, 2,
						    ATOM_DEVICE_TV1_SUPPORT,
						    DRM_MODE_CONNECTOR_SVIDEO,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_SVIDEO,
						    &hpd);
		}
		break;
	case CT_IBOOK:
		DRM_INFO("Connector Table: %d (ibook)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* VGA - TV DAC */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_POWERBOOK_EXTERNAL:
		DRM_INFO("Connector Table: %d (powerbook external tmds)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* DVI-I - primary dac, ext tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP2_SUPPORT,
								0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		/* XXX some are SL */
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_POWERBOOK_INTERNAL:
		DRM_INFO("Connector Table: %d (powerbook internal tmds)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* DVI-I - primary dac, int tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_POWERBOOK_VGA:
		DRM_INFO("Connector Table: %d (powerbook vga)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_MINI_EXTERNAL:
		DRM_INFO("Connector Table: %d (mini external tmds)\n",
			 rdev->mode_info.connector_table);
		/* DVI-I - tv dac, ext tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP2_SUPPORT,
								0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		/* XXX are any DL? */
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_MINI_INTERNAL:
		DRM_INFO("Connector Table: %d (mini internal tmds)\n",
			 rdev->mode_info.connector_table);
		/* DVI-I - tv dac, int tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_IMAC_G5_ISIGHT:
		DRM_INFO("Connector Table: %d (imac g5 isight)\n",
			 rdev->mode_info.connector_table);
		/* DVI-D - int tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_DFP1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVID, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D,
					    &hpd);
		/* VGA - tv dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_EMAC:
		DRM_INFO("Connector Table: %d (emac)\n",
			 rdev->mode_info.connector_table);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* VGA - tv dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_RN50_POWER:
		DRM_INFO("Connector Table: %d (rn50-power)\n",
			 rdev->mode_info.connector_table);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		break;
	case CT_MAC_X800:
		DRM_INFO("Connector Table: %d (mac x800)\n",
			 rdev->mode_info.connector_table);
		/* DVI - primary dac, internal tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_DFP1_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_CRT1_SUPPORT,
								  1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* DVI - tv dac, dvo */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_DFP2_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_CRT2_SUPPORT,
								  2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I,
					    &hpd);
		break;
	case CT_MAC_G5_9600:
		DRM_INFO("Connector Table: %d (mac g5 9600)\n",
			 rdev->mode_info.connector_table);
		/* DVI - tv dac, dvo */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_DFP2_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_CRT2_SUPPORT,
								  2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* ADC - primary dac, internal tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_DFP1_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								  ATOM_DEVICE_CRT1_SUPPORT,
								  1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_SAM440EP:
		DRM_INFO("Connector Table: %d (SAM440ep embedded board)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_NONE_DETECTED, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* DVI-I - secondary dac, int tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 2,
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 3, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	case CT_MAC_G4_SILVER:
		DRM_INFO("Connector Table: %d (mac g4 silver)\n",
			 rdev->mode_info.connector_table);
		/* DVI-I - tv dac, int tmds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_enum(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		break;
	default:
		DRM_INFO("Connector table: %d (invalid)\n",
			 rdev->mode_info.connector_table);
		return false;
	}

	radeon_link_encoder_connector(dev);

	return true;
}