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

/* Variables and functions */
 int /*<<< orphan*/  FF_ARRAY_ELEMS (char**) ; 
 int TIFF_ANGULAR_UNIT_OFFSET ; 
 int TIFF_COORD_TRANS_OFFSET ; 
 int TIFF_ELLIPSOID_OFFSET ; 
 int TIFF_GCSE_TYPE_OFFSET ; 
 int TIFF_GCS_TYPE_OFFSET ; 
 int TIFF_GEODETIC_DATUM_E_OFFSET ; 
 int TIFF_GEODETIC_DATUM_OFFSET ; 
#define  TIFF_GEOGRAPHIC_TYPE_GEOKEY 142 
#define  TIFF_GEOG_ANGULAR_UNITS_GEOKEY 141 
#define  TIFF_GEOG_AZIMUTH_UNITS_GEOKEY 140 
#define  TIFF_GEOG_ELLIPSOID_GEOKEY 139 
#define  TIFF_GEOG_GEODETIC_DATUM_GEOKEY 138 
#define  TIFF_GEOG_LINEAR_UNITS_GEOKEY 137 
#define  TIFF_GEOG_PRIME_MERIDIAN_GEOKEY 136 
 int TIFF_GEO_KEY_UNDEFINED ; 
 int TIFF_GEO_KEY_USER_DEFINED ; 
#define  TIFF_GT_MODEL_TYPE_GEOKEY 135 
 int TIFF_GT_MODEL_TYPE_OFFSET ; 
#define  TIFF_GT_RASTER_TYPE_GEOKEY 134 
 int TIFF_GT_RASTER_TYPE_OFFSET ; 
 int TIFF_LINEAR_UNIT_OFFSET ; 
 int TIFF_ORTHO_VERT_CS_OFFSET ; 
 int TIFF_PRIME_MERIDIAN_OFFSET ; 
#define  TIFF_PROJECTED_CS_TYPE_GEOKEY 133 
#define  TIFF_PROJECTION_GEOKEY 132 
#define  TIFF_PROJ_COORD_TRANS_GEOKEY 131 
#define  TIFF_PROJ_LINEAR_UNITS_GEOKEY 130 
#define  TIFF_VERTICAL_CS_TYPE_GEOKEY 129 
#define  TIFF_VERTICAL_UNITS_GEOKEY 128 
 int TIFF_VERT_CS_OFFSET ; 
 char* av_malloc (int) ; 
 char* av_strdup (char*) ; 
 char** ff_tiff_angular_unit_codes ; 
 char** ff_tiff_coord_trans_codes ; 
 char** ff_tiff_ellipsoid_codes ; 
 char** ff_tiff_gcs_type_codes ; 
 char** ff_tiff_gcse_type_codes ; 
 char** ff_tiff_geodetic_datum_codes ; 
 char** ff_tiff_geodetic_datum_e_codes ; 
 char** ff_tiff_gt_model_type_codes ; 
 char** ff_tiff_gt_raster_type_codes ; 
 char** ff_tiff_linear_unit_codes ; 
 char** ff_tiff_ortho_vert_cs_codes ; 
 char** ff_tiff_prime_meridian_codes ; 
 char** ff_tiff_proj_cs_type_codes ; 
 char** ff_tiff_projection_codes ; 
 char** ff_tiff_vert_cs_codes ; 
 char* search_keyval (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *get_geokey_val(int key, int val)
{
    char *ap;

    if (val == TIFF_GEO_KEY_UNDEFINED)
        return av_strdup("undefined");
    if (val == TIFF_GEO_KEY_USER_DEFINED)
        return av_strdup("User-Defined");

#define RET_GEOKEY_VAL(TYPE, array)\
    if (val >= TIFF_##TYPE##_OFFSET &&\
        val - TIFF_##TYPE##_OFFSET < FF_ARRAY_ELEMS(ff_tiff_##array##_codes))\
        return av_strdup(ff_tiff_##array##_codes[val - TIFF_##TYPE##_OFFSET]);

    switch (key) {
    case TIFF_GT_MODEL_TYPE_GEOKEY:
        RET_GEOKEY_VAL(GT_MODEL_TYPE, gt_model_type);
        break;
    case TIFF_GT_RASTER_TYPE_GEOKEY:
        RET_GEOKEY_VAL(GT_RASTER_TYPE, gt_raster_type);
        break;
    case TIFF_GEOG_LINEAR_UNITS_GEOKEY:
    case TIFF_PROJ_LINEAR_UNITS_GEOKEY:
    case TIFF_VERTICAL_UNITS_GEOKEY:
        RET_GEOKEY_VAL(LINEAR_UNIT, linear_unit);
        break;
    case TIFF_GEOG_ANGULAR_UNITS_GEOKEY:
    case TIFF_GEOG_AZIMUTH_UNITS_GEOKEY:
        RET_GEOKEY_VAL(ANGULAR_UNIT, angular_unit);
        break;
    case TIFF_GEOGRAPHIC_TYPE_GEOKEY:
        RET_GEOKEY_VAL(GCS_TYPE, gcs_type);
        RET_GEOKEY_VAL(GCSE_TYPE, gcse_type);
        break;
    case TIFF_GEOG_GEODETIC_DATUM_GEOKEY:
        RET_GEOKEY_VAL(GEODETIC_DATUM, geodetic_datum);
        RET_GEOKEY_VAL(GEODETIC_DATUM_E, geodetic_datum_e);
        break;
    case TIFF_GEOG_ELLIPSOID_GEOKEY:
        RET_GEOKEY_VAL(ELLIPSOID, ellipsoid);
        break;
    case TIFF_GEOG_PRIME_MERIDIAN_GEOKEY:
        RET_GEOKEY_VAL(PRIME_MERIDIAN, prime_meridian);
        break;
    case TIFF_PROJECTED_CS_TYPE_GEOKEY:
        ap = av_strdup(search_keyval(ff_tiff_proj_cs_type_codes, FF_ARRAY_ELEMS(ff_tiff_proj_cs_type_codes), val));
        if(ap) return ap;
        break;
    case TIFF_PROJECTION_GEOKEY:
        ap = av_strdup(search_keyval(ff_tiff_projection_codes, FF_ARRAY_ELEMS(ff_tiff_projection_codes), val));
        if(ap) return ap;
        break;
    case TIFF_PROJ_COORD_TRANS_GEOKEY:
        RET_GEOKEY_VAL(COORD_TRANS, coord_trans);
        break;
    case TIFF_VERTICAL_CS_TYPE_GEOKEY:
        RET_GEOKEY_VAL(VERT_CS, vert_cs);
        RET_GEOKEY_VAL(ORTHO_VERT_CS, ortho_vert_cs);
        break;

    }

    ap = av_malloc(14);
    if (ap)
        snprintf(ap, 14, "Unknown-%d", val);
    return ap;
}