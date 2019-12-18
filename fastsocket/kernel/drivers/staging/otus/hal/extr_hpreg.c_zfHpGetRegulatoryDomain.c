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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
struct TYPE_3__ {int regionCode; } ;
struct TYPE_4__ {TYPE_1__ regulationTable; } ;

/* Variables and functions */
#define  ETSI1 230 
#define  ETSI1_WORLD 229 
#define  ETSI2 228 
#define  ETSI2_WORLD 227 
#define  ETSI3 226 
#define  ETSI3_ETSIA 225 
#define  ETSI3_WORLD 224 
#define  ETSI4 223 
#define  ETSI4_ETSIC 222 
#define  ETSI4_WORLD 221 
#define  ETSI5 220 
#define  ETSI5_WORLD 219 
#define  ETSI6 218 
#define  ETSI6_WORLD 217 
#define  ETSIA 216 
#define  ETSIB 215 
#define  ETSIC 214 
#define  ETSI_RESERVED 213 
#define  FCC1 212 
#define  FCC1_FCCA 211 
#define  FCC1_WORLD 210 
#define  FCC2 209 
#define  FCC2_ETSIC 208 
#define  FCC2_FCCA 207 
#define  FCC2_WORLD 206 
#define  FCC3 205 
#define  FCC3_FCCA 204 
#define  FCC3_WORLD 203 
#define  FCC4 202 
#define  FCC4_FCCA 201 
#define  FCC5 200 
#define  FCC5_FCCA 199 
#define  FCCA 198 
#define  MKK1 197 
#define  MKK10 196 
#define  MKK10_FCCA 195 
#define  MKK10_MKKA 194 
#define  MKK10_MKKA1 193 
#define  MKK10_MKKA2 192 
#define  MKK10_MKKC 191 
#define  MKK11 190 
#define  MKK11_FCCA 189 
#define  MKK11_MKKA 188 
#define  MKK11_MKKA1 187 
#define  MKK11_MKKA2 186 
#define  MKK11_MKKC 185 
#define  MKK12 184 
#define  MKK12_FCCA 183 
#define  MKK12_MKKA 182 
#define  MKK12_MKKA1 181 
#define  MKK12_MKKA2 180 
#define  MKK12_MKKC 179 
#define  MKK1_FCCA 178 
#define  MKK1_MKKA 177 
#define  MKK1_MKKA1 176 
#define  MKK1_MKKA2 175 
#define  MKK1_MKKB 174 
#define  MKK1_MKKC 173 
#define  MKK2 172 
#define  MKK2_MKKA 171 
#define  MKK3 170 
#define  MKK3_FCCA 169 
#define  MKK3_MKKA 168 
#define  MKK3_MKKA1 167 
#define  MKK3_MKKA2 166 
#define  MKK3_MKKB 165 
#define  MKK3_MKKC 164 
#define  MKK4 163 
#define  MKK4_FCCA 162 
#define  MKK4_MKKA 161 
#define  MKK4_MKKA1 160 
#define  MKK4_MKKA2 159 
#define  MKK4_MKKB 158 
#define  MKK4_MKKC 157 
#define  MKK5 156 
#define  MKK5_MKKA2 155 
#define  MKK5_MKKB 154 
#define  MKK5_MKKC 153 
#define  MKK6 152 
#define  MKK6_FCCA 151 
#define  MKK6_MKKA1 150 
#define  MKK6_MKKA2 149 
#define  MKK6_MKKB 148 
#define  MKK6_MKKC 147 
#define  MKK7 146 
#define  MKK7_FCCA 145 
#define  MKK7_MKKA 144 
#define  MKK7_MKKA1 143 
#define  MKK7_MKKB 142 
#define  MKK7_MKKC 141 
#define  MKK8 140 
#define  MKK8_MKKA2 139 
#define  MKK8_MKKB 138 
#define  MKK8_MKKC 137 
#define  MKK9 136 
#define  MKK9_FCCA 135 
#define  MKK9_MKKA 134 
#define  MKK9_MKKA1 133 
#define  MKK9_MKKA2 132 
#define  MKK9_MKKC 131 
#define  MKKA 130 
#define  MKKC 129 
#define  NO_ENUMRD 128 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfHpGetRegulatoryDomain(zdev_t* dev)
{
    zmw_get_wlan_dev(dev);

    switch (wd->regulationTable.regionCode)
    {
        case NO_ENUMRD:
            return 0;
            break;
        case FCC1_FCCA:
        case FCC1_WORLD:
        case FCC4_FCCA:
        case FCC5_FCCA:
        case FCC2_WORLD:
        case FCC2_ETSIC:
        case FCC3_FCCA:
        case FCC3_WORLD:
        case FCC1:
        case FCC2:
        case FCC3:
        case FCC4:
        case FCC5:
        case FCCA:
            return 0x10;//WG_AMERICAS DOT11_REG_DOMAIN_FCC  United States
            break;

        case FCC2_FCCA:
            return 0x20;//DOT11_REG_DOMAIN_DOC  Canada
            break;

        case ETSI1_WORLD:
        case ETSI3_ETSIA:
        case ETSI2_WORLD:
        case ETSI3_WORLD:
        case ETSI4_WORLD:
        case ETSI4_ETSIC:
        case ETSI5_WORLD:
        case ETSI6_WORLD:
        case ETSI_RESERVED:
        case ETSI1:
        case ETSI2:
        case ETSI3:
        case ETSI4:
        case ETSI5:
        case ETSI6:
        case ETSIA:
        case ETSIB:
        case ETSIC:
            return 0x30;//WG_EMEA DOT11_REG_DOMAIN_ETSI  Most of Europe
            break;

        case MKK1_MKKA:
        case MKK1_MKKB:
        case MKK2_MKKA:
        case MKK1_FCCA:
        case MKK1_MKKA1:
        case MKK1_MKKA2:
        case MKK1_MKKC:
        case MKK3_MKKB:
        case MKK3_MKKA2:
        case MKK3_MKKC:
        case MKK4_MKKB:
        case MKK4_MKKA2:
        case MKK4_MKKC:
        case MKK5_MKKB:
        case MKK5_MKKA2:
        case MKK5_MKKC:
        case MKK6_MKKB:
        case MKK6_MKKA2:
        case MKK6_MKKC:
        case MKK7_MKKB:
        case MKK7_MKKA:
        case MKK7_MKKC:
        case MKK8_MKKB:
        case MKK8_MKKA2:
        case MKK8_MKKC:
        case MKK6_MKKA1:
        case MKK6_FCCA:
        case MKK7_MKKA1:
        case MKK7_FCCA:
        case MKK9_FCCA:
        case MKK9_MKKA1:
        case MKK9_MKKC:
        case MKK9_MKKA2:
        case MKK10_FCCA:
        case MKK10_MKKA1:
        case MKK10_MKKC:
        case MKK10_MKKA2:
        case MKK11_MKKA:
        case MKK11_FCCA:
        case MKK11_MKKA1:
        case MKK11_MKKC:
        case MKK11_MKKA2:
        case MKK12_MKKA:
        case MKK12_FCCA:
        case MKK12_MKKA1:
        case MKK12_MKKC:
        case MKK12_MKKA2:
        case MKK3_MKKA:
        case MKK3_MKKA1:
        case MKK3_FCCA:
        case MKK4_MKKA:
        case MKK4_MKKA1:
        case MKK4_FCCA:
        case MKK9_MKKA:
        case MKK10_MKKA:
        case MKK1:
        case MKK2:
        case MKK3:
        case MKK4:
        case MKK5:
        case MKK6:
        case MKK7:
        case MKK8:
        case MKK9:
        case MKK10:
        case MKK11:
        case MKK12:
        case MKKA:
        case MKKC:
            return 0x40;//WG_JAPAN DOT11_REG_DOMAIN_MKK  Japan
            break;

        default:
            break;
    }
    return 0xFF;// Didn't input RegDmn by mean to distinguish by customer

}