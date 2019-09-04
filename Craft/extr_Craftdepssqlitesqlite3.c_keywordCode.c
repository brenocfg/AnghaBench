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
#define  TK_ABORT 237 
#define  TK_ACTION 236 
#define  TK_ADD 235 
#define  TK_AFTER 234 
#define  TK_ALL 233 
#define  TK_ALTER 232 
#define  TK_ANALYZE 231 
#define  TK_AND 230 
#define  TK_AS 229 
#define  TK_ASC 228 
#define  TK_ATTACH 227 
#define  TK_AUTOINCR 226 
#define  TK_BEFORE 225 
#define  TK_BEGIN 224 
#define  TK_BETWEEN 223 
#define  TK_BY 222 
#define  TK_CASCADE 221 
#define  TK_CASE 220 
#define  TK_CAST 219 
#define  TK_CHECK 218 
#define  TK_COLLATE 217 
#define  TK_COLUMNKW 216 
#define  TK_COMMIT 215 
#define  TK_CONFLICT 214 
#define  TK_CONSTRAINT 213 
#define  TK_CREATE 212 
#define  TK_CTIME_KW 211 
#define  TK_DATABASE 210 
#define  TK_DEFAULT 209 
#define  TK_DEFERRABLE 208 
#define  TK_DEFERRED 207 
#define  TK_DELETE 206 
#define  TK_DESC 205 
#define  TK_DETACH 204 
#define  TK_DISTINCT 203 
#define  TK_DROP 202 
#define  TK_EACH 201 
#define  TK_ELSE 200 
#define  TK_END 199 
#define  TK_ESCAPE 198 
#define  TK_EXCEPT 197 
#define  TK_EXCLUSIVE 196 
#define  TK_EXISTS 195 
#define  TK_EXPLAIN 194 
#define  TK_FAIL 193 
#define  TK_FOR 192 
#define  TK_FOREIGN 191 
#define  TK_FROM 190 
#define  TK_GROUP 189 
#define  TK_HAVING 188 
 int TK_ID ; 
#define  TK_IF 187 
#define  TK_IGNORE 186 
#define  TK_IMMEDIATE 185 
#define  TK_IN 184 
#define  TK_INDEX 183 
#define  TK_INDEXED 182 
#define  TK_INITIALLY 181 
#define  TK_INSERT 180 
#define  TK_INSTEAD 179 
#define  TK_INTERSECT 178 
#define  TK_INTO 177 
#define  TK_IS 176 
#define  TK_ISNULL 175 
#define  TK_JOIN 174 
#define  TK_JOIN_KW 173 
#define  TK_KEY 172 
#define  TK_LIKE_KW 171 
#define  TK_LIMIT 170 
#define  TK_MATCH 169 
#define  TK_NO 168 
#define  TK_NOT 167 
#define  TK_NOTNULL 166 
#define  TK_NULL 165 
#define  TK_OF 164 
#define  TK_OFFSET 163 
#define  TK_ON 162 
#define  TK_OR 161 
#define  TK_ORDER 160 
#define  TK_PLAN 159 
#define  TK_PRAGMA 158 
#define  TK_PRIMARY 157 
#define  TK_QUERY 156 
#define  TK_RAISE 155 
#define  TK_REFERENCES 154 
#define  TK_REINDEX 153 
#define  TK_RELEASE 152 
#define  TK_RENAME 151 
#define  TK_REPLACE 150 
#define  TK_RESTRICT 149 
#define  TK_ROLLBACK 148 
#define  TK_ROW 147 
#define  TK_SAVEPOINT 146 
#define  TK_SELECT 145 
#define  TK_SET 144 
#define  TK_TABLE 143 
#define  TK_TEMP 142 
#define  TK_THEN 141 
#define  TK_TO 140 
#define  TK_TRANSACTION 139 
#define  TK_TRIGGER 138 
#define  TK_UNION 137 
#define  TK_UNIQUE 136 
#define  TK_UPDATE 135 
#define  TK_USING 134 
#define  TK_VACUUM 133 
#define  TK_VALUES 132 
#define  TK_VIEW 131 
#define  TK_VIRTUAL 130 
#define  TK_WHEN 129 
#define  TK_WHERE 128 
 int charMap (char const) ; 
 scalar_t__ sqlite3StrNICmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int keywordCode(const char *z, int n){
  /* zText[] encodes 811 bytes of keywords in 541 bytes */
  /*   REINDEXEDESCAPEACHECKEYBEFOREIGNOREGEXPLAINSTEADDATABASELECT       */
  /*   ABLEFTHENDEFERRABLELSEXCEPTRANSACTIONATURALTERAISEXCLUSIVE         */
  /*   XISTSAVEPOINTERSECTRIGGEREFERENCESCONSTRAINTOFFSETEMPORARY         */
  /*   UNIQUERYATTACHAVINGROUPDATEBEGINNERELEASEBETWEENOTNULLIKE          */
  /*   CASCADELETECASECOLLATECREATECURRENT_DATEDETACHIMMEDIATEJOIN        */
  /*   SERTMATCHPLANALYZEPRAGMABORTVALUESVIRTUALIMITWHENWHERENAME         */
  /*   AFTEREPLACEANDEFAULTAUTOINCREMENTCASTCOLUMNCOMMITCONFLICTCROSS     */
  /*   CURRENT_TIMESTAMPRIMARYDEFERREDISTINCTDROPFAILFROMFULLGLOBYIF      */
  /*   ISNULLORDERESTRICTOUTERIGHTROLLBACKROWUNIONUSINGVACUUMVIEW         */
  /*   INITIALLY                                                          */
  static const char zText[540] = {
    'R','E','I','N','D','E','X','E','D','E','S','C','A','P','E','A','C','H',
    'E','C','K','E','Y','B','E','F','O','R','E','I','G','N','O','R','E','G',
    'E','X','P','L','A','I','N','S','T','E','A','D','D','A','T','A','B','A',
    'S','E','L','E','C','T','A','B','L','E','F','T','H','E','N','D','E','F',
    'E','R','R','A','B','L','E','L','S','E','X','C','E','P','T','R','A','N',
    'S','A','C','T','I','O','N','A','T','U','R','A','L','T','E','R','A','I',
    'S','E','X','C','L','U','S','I','V','E','X','I','S','T','S','A','V','E',
    'P','O','I','N','T','E','R','S','E','C','T','R','I','G','G','E','R','E',
    'F','E','R','E','N','C','E','S','C','O','N','S','T','R','A','I','N','T',
    'O','F','F','S','E','T','E','M','P','O','R','A','R','Y','U','N','I','Q',
    'U','E','R','Y','A','T','T','A','C','H','A','V','I','N','G','R','O','U',
    'P','D','A','T','E','B','E','G','I','N','N','E','R','E','L','E','A','S',
    'E','B','E','T','W','E','E','N','O','T','N','U','L','L','I','K','E','C',
    'A','S','C','A','D','E','L','E','T','E','C','A','S','E','C','O','L','L',
    'A','T','E','C','R','E','A','T','E','C','U','R','R','E','N','T','_','D',
    'A','T','E','D','E','T','A','C','H','I','M','M','E','D','I','A','T','E',
    'J','O','I','N','S','E','R','T','M','A','T','C','H','P','L','A','N','A',
    'L','Y','Z','E','P','R','A','G','M','A','B','O','R','T','V','A','L','U',
    'E','S','V','I','R','T','U','A','L','I','M','I','T','W','H','E','N','W',
    'H','E','R','E','N','A','M','E','A','F','T','E','R','E','P','L','A','C',
    'E','A','N','D','E','F','A','U','L','T','A','U','T','O','I','N','C','R',
    'E','M','E','N','T','C','A','S','T','C','O','L','U','M','N','C','O','M',
    'M','I','T','C','O','N','F','L','I','C','T','C','R','O','S','S','C','U',
    'R','R','E','N','T','_','T','I','M','E','S','T','A','M','P','R','I','M',
    'A','R','Y','D','E','F','E','R','R','E','D','I','S','T','I','N','C','T',
    'D','R','O','P','F','A','I','L','F','R','O','M','F','U','L','L','G','L',
    'O','B','Y','I','F','I','S','N','U','L','L','O','R','D','E','R','E','S',
    'T','R','I','C','T','O','U','T','E','R','I','G','H','T','R','O','L','L',
    'B','A','C','K','R','O','W','U','N','I','O','N','U','S','I','N','G','V',
    'A','C','U','U','M','V','I','E','W','I','N','I','T','I','A','L','L','Y',
  };
  static const unsigned char aHash[127] = {
      72, 101, 114,  70,   0,  45,   0,   0,  78,   0,  73,   0,   0,
      42,  12,  74,  15,   0, 113,  81,  50, 108,   0,  19,   0,   0,
     118,   0, 116, 111,   0,  22,  89,   0,   9,   0,   0,  66,  67,
       0,  65,   6,   0,  48,  86,  98,   0, 115,  97,   0,   0,  44,
       0,  99,  24,   0,  17,   0, 119,  49,  23,   0,   5, 106,  25,
      92,   0,   0, 121, 102,  56, 120,  53,  28,  51,   0,  87,   0,
      96,  26,   0,  95,   0,   0,   0,  91,  88,  93,  84, 105,  14,
      39, 104,   0,  77,   0,  18,  85, 107,  32,   0, 117,  76, 109,
      58,  46,  80,   0,   0,  90,  40,   0, 112,   0,  36,   0,   0,
      29,   0,  82,  59,  60,   0,  20,  57,   0,  52,
  };
  static const unsigned char aNext[121] = {
       0,   0,   0,   0,   4,   0,   0,   0,   0,   0,   0,   0,   0,
       0,   2,   0,   0,   0,   0,   0,   0,  13,   0,   0,   0,   0,
       0,   7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,  33,   0,  21,   0,   0,   0,  43,   3,  47,
       0,   0,   0,   0,  30,   0,  54,   0,  38,   0,   0,   0,   1,
      62,   0,   0,  63,   0,  41,   0,   0,   0,   0,   0,   0,   0,
      61,   0,   0,   0,   0,  31,  55,  16,  34,  10,   0,   0,   0,
       0,   0,   0,   0,  11,  68,  75,   0,   8,   0, 100,  94,   0,
     103,   0,  83,   0,  71,   0,   0, 110,  27,  37,  69,  79,   0,
      35,  64,   0,   0,
  };
  static const unsigned char aLen[121] = {
       7,   7,   5,   4,   6,   4,   5,   3,   6,   7,   3,   6,   6,
       7,   7,   3,   8,   2,   6,   5,   4,   4,   3,  10,   4,   6,
      11,   6,   2,   7,   5,   5,   9,   6,   9,   9,   7,  10,  10,
       4,   6,   2,   3,   9,   4,   2,   6,   5,   6,   6,   5,   6,
       5,   5,   7,   7,   7,   3,   2,   4,   4,   7,   3,   6,   4,
       7,   6,  12,   6,   9,   4,   6,   5,   4,   7,   6,   5,   6,
       7,   5,   4,   5,   6,   5,   7,   3,   7,  13,   2,   2,   4,
       6,   6,   8,   5,  17,  12,   7,   8,   8,   2,   4,   4,   4,
       4,   4,   2,   2,   6,   5,   8,   5,   5,   8,   3,   5,   5,
       6,   4,   9,   3,
  };
  static const unsigned short int aOffset[121] = {
       0,   2,   2,   8,   9,  14,  16,  20,  23,  25,  25,  29,  33,
      36,  41,  46,  48,  53,  54,  59,  62,  65,  67,  69,  78,  81,
      86,  91,  95,  96, 101, 105, 109, 117, 122, 128, 136, 142, 152,
     159, 162, 162, 165, 167, 167, 171, 176, 179, 184, 189, 194, 197,
     203, 206, 210, 217, 223, 223, 223, 226, 229, 233, 234, 238, 244,
     248, 255, 261, 273, 279, 288, 290, 296, 301, 303, 310, 315, 320,
     326, 332, 337, 341, 344, 350, 354, 361, 363, 370, 372, 374, 383,
     387, 393, 399, 407, 412, 412, 428, 435, 442, 443, 450, 454, 458,
     462, 466, 469, 471, 473, 479, 483, 491, 495, 500, 508, 511, 516,
     521, 527, 531, 536,
  };
  static const unsigned char aCode[121] = {
    TK_REINDEX,    TK_INDEXED,    TK_INDEX,      TK_DESC,       TK_ESCAPE,     
    TK_EACH,       TK_CHECK,      TK_KEY,        TK_BEFORE,     TK_FOREIGN,    
    TK_FOR,        TK_IGNORE,     TK_LIKE_KW,    TK_EXPLAIN,    TK_INSTEAD,    
    TK_ADD,        TK_DATABASE,   TK_AS,         TK_SELECT,     TK_TABLE,      
    TK_JOIN_KW,    TK_THEN,       TK_END,        TK_DEFERRABLE, TK_ELSE,       
    TK_EXCEPT,     TK_TRANSACTION,TK_ACTION,     TK_ON,         TK_JOIN_KW,    
    TK_ALTER,      TK_RAISE,      TK_EXCLUSIVE,  TK_EXISTS,     TK_SAVEPOINT,  
    TK_INTERSECT,  TK_TRIGGER,    TK_REFERENCES, TK_CONSTRAINT, TK_INTO,       
    TK_OFFSET,     TK_OF,         TK_SET,        TK_TEMP,       TK_TEMP,       
    TK_OR,         TK_UNIQUE,     TK_QUERY,      TK_ATTACH,     TK_HAVING,     
    TK_GROUP,      TK_UPDATE,     TK_BEGIN,      TK_JOIN_KW,    TK_RELEASE,    
    TK_BETWEEN,    TK_NOTNULL,    TK_NOT,        TK_NO,         TK_NULL,       
    TK_LIKE_KW,    TK_CASCADE,    TK_ASC,        TK_DELETE,     TK_CASE,       
    TK_COLLATE,    TK_CREATE,     TK_CTIME_KW,   TK_DETACH,     TK_IMMEDIATE,  
    TK_JOIN,       TK_INSERT,     TK_MATCH,      TK_PLAN,       TK_ANALYZE,    
    TK_PRAGMA,     TK_ABORT,      TK_VALUES,     TK_VIRTUAL,    TK_LIMIT,      
    TK_WHEN,       TK_WHERE,      TK_RENAME,     TK_AFTER,      TK_REPLACE,    
    TK_AND,        TK_DEFAULT,    TK_AUTOINCR,   TK_TO,         TK_IN,         
    TK_CAST,       TK_COLUMNKW,   TK_COMMIT,     TK_CONFLICT,   TK_JOIN_KW,    
    TK_CTIME_KW,   TK_CTIME_KW,   TK_PRIMARY,    TK_DEFERRED,   TK_DISTINCT,   
    TK_IS,         TK_DROP,       TK_FAIL,       TK_FROM,       TK_JOIN_KW,    
    TK_LIKE_KW,    TK_BY,         TK_IF,         TK_ISNULL,     TK_ORDER,      
    TK_RESTRICT,   TK_JOIN_KW,    TK_JOIN_KW,    TK_ROLLBACK,   TK_ROW,        
    TK_UNION,      TK_USING,      TK_VACUUM,     TK_VIEW,       TK_INITIALLY,  
    TK_ALL,        
  };
  int h, i;
  if( n<2 ) return TK_ID;
  h = ((charMap(z[0])*4) ^
      (charMap(z[n-1])*3) ^
      n) % 127;
  for(i=((int)aHash[h])-1; i>=0; i=((int)aNext[i])-1){
    if( aLen[i]==n && sqlite3StrNICmp(&zText[aOffset[i]],z,n)==0 ){
      testcase( i==0 ); /* REINDEX */
      testcase( i==1 ); /* INDEXED */
      testcase( i==2 ); /* INDEX */
      testcase( i==3 ); /* DESC */
      testcase( i==4 ); /* ESCAPE */
      testcase( i==5 ); /* EACH */
      testcase( i==6 ); /* CHECK */
      testcase( i==7 ); /* KEY */
      testcase( i==8 ); /* BEFORE */
      testcase( i==9 ); /* FOREIGN */
      testcase( i==10 ); /* FOR */
      testcase( i==11 ); /* IGNORE */
      testcase( i==12 ); /* REGEXP */
      testcase( i==13 ); /* EXPLAIN */
      testcase( i==14 ); /* INSTEAD */
      testcase( i==15 ); /* ADD */
      testcase( i==16 ); /* DATABASE */
      testcase( i==17 ); /* AS */
      testcase( i==18 ); /* SELECT */
      testcase( i==19 ); /* TABLE */
      testcase( i==20 ); /* LEFT */
      testcase( i==21 ); /* THEN */
      testcase( i==22 ); /* END */
      testcase( i==23 ); /* DEFERRABLE */
      testcase( i==24 ); /* ELSE */
      testcase( i==25 ); /* EXCEPT */
      testcase( i==26 ); /* TRANSACTION */
      testcase( i==27 ); /* ACTION */
      testcase( i==28 ); /* ON */
      testcase( i==29 ); /* NATURAL */
      testcase( i==30 ); /* ALTER */
      testcase( i==31 ); /* RAISE */
      testcase( i==32 ); /* EXCLUSIVE */
      testcase( i==33 ); /* EXISTS */
      testcase( i==34 ); /* SAVEPOINT */
      testcase( i==35 ); /* INTERSECT */
      testcase( i==36 ); /* TRIGGER */
      testcase( i==37 ); /* REFERENCES */
      testcase( i==38 ); /* CONSTRAINT */
      testcase( i==39 ); /* INTO */
      testcase( i==40 ); /* OFFSET */
      testcase( i==41 ); /* OF */
      testcase( i==42 ); /* SET */
      testcase( i==43 ); /* TEMPORARY */
      testcase( i==44 ); /* TEMP */
      testcase( i==45 ); /* OR */
      testcase( i==46 ); /* UNIQUE */
      testcase( i==47 ); /* QUERY */
      testcase( i==48 ); /* ATTACH */
      testcase( i==49 ); /* HAVING */
      testcase( i==50 ); /* GROUP */
      testcase( i==51 ); /* UPDATE */
      testcase( i==52 ); /* BEGIN */
      testcase( i==53 ); /* INNER */
      testcase( i==54 ); /* RELEASE */
      testcase( i==55 ); /* BETWEEN */
      testcase( i==56 ); /* NOTNULL */
      testcase( i==57 ); /* NOT */
      testcase( i==58 ); /* NO */
      testcase( i==59 ); /* NULL */
      testcase( i==60 ); /* LIKE */
      testcase( i==61 ); /* CASCADE */
      testcase( i==62 ); /* ASC */
      testcase( i==63 ); /* DELETE */
      testcase( i==64 ); /* CASE */
      testcase( i==65 ); /* COLLATE */
      testcase( i==66 ); /* CREATE */
      testcase( i==67 ); /* CURRENT_DATE */
      testcase( i==68 ); /* DETACH */
      testcase( i==69 ); /* IMMEDIATE */
      testcase( i==70 ); /* JOIN */
      testcase( i==71 ); /* INSERT */
      testcase( i==72 ); /* MATCH */
      testcase( i==73 ); /* PLAN */
      testcase( i==74 ); /* ANALYZE */
      testcase( i==75 ); /* PRAGMA */
      testcase( i==76 ); /* ABORT */
      testcase( i==77 ); /* VALUES */
      testcase( i==78 ); /* VIRTUAL */
      testcase( i==79 ); /* LIMIT */
      testcase( i==80 ); /* WHEN */
      testcase( i==81 ); /* WHERE */
      testcase( i==82 ); /* RENAME */
      testcase( i==83 ); /* AFTER */
      testcase( i==84 ); /* REPLACE */
      testcase( i==85 ); /* AND */
      testcase( i==86 ); /* DEFAULT */
      testcase( i==87 ); /* AUTOINCREMENT */
      testcase( i==88 ); /* TO */
      testcase( i==89 ); /* IN */
      testcase( i==90 ); /* CAST */
      testcase( i==91 ); /* COLUMN */
      testcase( i==92 ); /* COMMIT */
      testcase( i==93 ); /* CONFLICT */
      testcase( i==94 ); /* CROSS */
      testcase( i==95 ); /* CURRENT_TIMESTAMP */
      testcase( i==96 ); /* CURRENT_TIME */
      testcase( i==97 ); /* PRIMARY */
      testcase( i==98 ); /* DEFERRED */
      testcase( i==99 ); /* DISTINCT */
      testcase( i==100 ); /* IS */
      testcase( i==101 ); /* DROP */
      testcase( i==102 ); /* FAIL */
      testcase( i==103 ); /* FROM */
      testcase( i==104 ); /* FULL */
      testcase( i==105 ); /* GLOB */
      testcase( i==106 ); /* BY */
      testcase( i==107 ); /* IF */
      testcase( i==108 ); /* ISNULL */
      testcase( i==109 ); /* ORDER */
      testcase( i==110 ); /* RESTRICT */
      testcase( i==111 ); /* OUTER */
      testcase( i==112 ); /* RIGHT */
      testcase( i==113 ); /* ROLLBACK */
      testcase( i==114 ); /* ROW */
      testcase( i==115 ); /* UNION */
      testcase( i==116 ); /* USING */
      testcase( i==117 ); /* VACUUM */
      testcase( i==118 ); /* VIEW */
      testcase( i==119 ); /* INITIALLY */
      testcase( i==120 ); /* ALL */
      return aCode[i];
    }
  }
  return TK_ID;
}